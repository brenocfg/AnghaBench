#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u64 ;
struct lmac {size_t dmacs_cfg; scalar_t__ dmacs_count; TYPE_1__* dmacs; } ;
struct TYPE_2__ {scalar_t__ dmac; int /*<<< orphan*/  vf_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (size_t) ; 

__attribute__((used)) static int bgx_lmac_save_filter(struct lmac *lmac, u64 dmac, u8 vf_id)
{
	u8 i = 0;

	if (!lmac)
		return -1;

	/* At the same time we could have several VFs 'attached' to some
	 * particular LMAC, and each VF is represented as network interface
	 * for kernel. So from user perspective it should be possible to
	 * manipulate with its' (VF) receive modes. However from PF
	 * driver perspective we need to keep track of filter configurations
	 * for different VFs to prevent filter values dupes
	 */
	for (i = 0; i < lmac->dmacs_cfg; i++) {
		if (lmac->dmacs[i].dmac == dmac) {
			lmac->dmacs[i].vf_map |= BIT_ULL(vf_id);
			return -1;
		}
	}

	if (!(lmac->dmacs_cfg < lmac->dmacs_count))
		return -1;

	/* keep it for further tracking */
	lmac->dmacs[lmac->dmacs_cfg].dmac = dmac;
	lmac->dmacs[lmac->dmacs_cfg].vf_map = BIT_ULL(vf_id);
	lmac->dmacs_cfg++;
	return 0;
}