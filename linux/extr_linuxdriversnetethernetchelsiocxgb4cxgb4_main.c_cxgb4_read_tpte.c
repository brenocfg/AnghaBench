#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  chip; } ;
struct TYPE_4__ {int start; } ;
struct TYPE_5__ {TYPE_1__ stag; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; int /*<<< orphan*/  win0_lock; TYPE_3__ params; TYPE_2__ vres; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EDRAM0_SIZE_G (int) ; 
 int EDRAM1_SIZE_G (int) ; 
 int EINVAL ; 
 int EXT_MEM0_SIZE_G (int) ; 
 int EXT_MEM1_SIZE_G (int) ; 
 int HMA_MUX_F ; 
 int /*<<< orphan*/  MA_EDRAM0_BAR_A ; 
 int /*<<< orphan*/  MA_EDRAM1_BAR_A ; 
 int /*<<< orphan*/  MA_EXT_MEMORY0_BAR_A ; 
 int /*<<< orphan*/  MA_EXT_MEMORY1_BAR_A ; 
 int /*<<< orphan*/  MA_TARGET_MEM_ENABLE_A ; 
 int MEM_EDC0 ; 
 int MEM_EDC1 ; 
 int MEM_HMA ; 
 int MEM_MC0 ; 
 int MEM_MC1 ; 
 int /*<<< orphan*/  T4_MEMORY_READ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ is_t5 (int /*<<< orphan*/ ) ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int t4_memory_rw (struct adapter*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

int cxgb4_read_tpte(struct net_device *dev, u32 stag, __be32 *tpte)
{
	u32 edc0_size, edc1_size, mc0_size, mc1_size, size;
	u32 edc0_end, edc1_end, mc0_end, mc1_end;
	u32 offset, memtype, memaddr;
	struct adapter *adap;
	u32 hma_size = 0;
	int ret;

	adap = netdev2adap(dev);

	offset = ((stag >> 8) * 32) + adap->vres.stag.start;

	/* Figure out where the offset lands in the Memory Type/Address scheme.
	 * This code assumes that the memory is laid out starting at offset 0
	 * with no breaks as: EDC0, EDC1, MC0, MC1. All cards have both EDC0
	 * and EDC1.  Some cards will have neither MC0 nor MC1, most cards have
	 * MC0, and some have both MC0 and MC1.
	 */
	size = t4_read_reg(adap, MA_EDRAM0_BAR_A);
	edc0_size = EDRAM0_SIZE_G(size) << 20;
	size = t4_read_reg(adap, MA_EDRAM1_BAR_A);
	edc1_size = EDRAM1_SIZE_G(size) << 20;
	size = t4_read_reg(adap, MA_EXT_MEMORY0_BAR_A);
	mc0_size = EXT_MEM0_SIZE_G(size) << 20;

	if (t4_read_reg(adap, MA_TARGET_MEM_ENABLE_A) & HMA_MUX_F) {
		size = t4_read_reg(adap, MA_EXT_MEMORY1_BAR_A);
		hma_size = EXT_MEM1_SIZE_G(size) << 20;
	}
	edc0_end = edc0_size;
	edc1_end = edc0_end + edc1_size;
	mc0_end = edc1_end + mc0_size;

	if (offset < edc0_end) {
		memtype = MEM_EDC0;
		memaddr = offset;
	} else if (offset < edc1_end) {
		memtype = MEM_EDC1;
		memaddr = offset - edc0_end;
	} else {
		if (hma_size && (offset < (edc1_end + hma_size))) {
			memtype = MEM_HMA;
			memaddr = offset - edc1_end;
		} else if (offset < mc0_end) {
			memtype = MEM_MC0;
			memaddr = offset - edc1_end;
		} else if (is_t5(adap->params.chip)) {
			size = t4_read_reg(adap, MA_EXT_MEMORY1_BAR_A);
			mc1_size = EXT_MEM1_SIZE_G(size) << 20;
			mc1_end = mc0_end + mc1_size;
			if (offset < mc1_end) {
				memtype = MEM_MC1;
				memaddr = offset - mc0_end;
			} else {
				/* offset beyond the end of any memory */
				goto err;
			}
		} else {
			/* T4/T6 only has a single memory channel */
			goto err;
		}
	}

	spin_lock(&adap->win0_lock);
	ret = t4_memory_rw(adap, 0, memtype, memaddr, 32, tpte, T4_MEMORY_READ);
	spin_unlock(&adap->win0_lock);
	return ret;

err:
	dev_err(adap->pdev_dev, "stag %#x, offset %#x out of range\n",
		stag, offset);
	return -EINVAL;
}