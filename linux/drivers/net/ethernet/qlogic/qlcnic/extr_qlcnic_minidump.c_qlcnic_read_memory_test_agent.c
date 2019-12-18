#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qlcnic_adapter {TYPE_2__* ahw; TYPE_1__* pdev; } ;
struct __mem {int size; int addr; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {int /*<<< orphan*/  mem_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int MAX_CTL_CHECK ; 
 int /*<<< orphan*/  QLCNIC_MS_ADDR_HI ; 
 int /*<<< orphan*/  QLCNIC_MS_ADDR_LO ; 
 int /*<<< orphan*/  QLCNIC_MS_CTRL ; 
 int QLCNIC_TA_START_ENABLE ; 
 int TA_CTL_BUSY ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ printk_ratelimit () ; 
 int qlcnic_ind_rd (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_ind_wr (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * qlcnic_ms_read_data ; 

__attribute__((used)) static u32 qlcnic_read_memory_test_agent(struct qlcnic_adapter *adapter,
					 struct __mem *mem, __le32 *buffer,
					 int *ret)
{
	u32 addr, data, test;
	int i, reg_read;

	reg_read = mem->size;
	addr = mem->addr;
	/* check for data size of multiple of 16 and 16 byte alignment */
	if ((addr & 0xf) || (reg_read%16)) {
		dev_info(&adapter->pdev->dev,
			 "Unaligned memory addr:0x%x size:0x%x\n",
			 addr, reg_read);
		*ret = -EINVAL;
		return 0;
	}

	mutex_lock(&adapter->ahw->mem_lock);

	while (reg_read != 0) {
		qlcnic_ind_wr(adapter, QLCNIC_MS_ADDR_LO, addr);
		qlcnic_ind_wr(adapter, QLCNIC_MS_ADDR_HI, 0);
		qlcnic_ind_wr(adapter, QLCNIC_MS_CTRL, QLCNIC_TA_START_ENABLE);

		for (i = 0; i < MAX_CTL_CHECK; i++) {
			test = qlcnic_ind_rd(adapter, QLCNIC_MS_CTRL);
			if (!(test & TA_CTL_BUSY))
				break;
		}
		if (i == MAX_CTL_CHECK) {
			if (printk_ratelimit()) {
				dev_err(&adapter->pdev->dev,
					"failed to read through agent\n");
				*ret = -EIO;
				goto out;
			}
		}
		for (i = 0; i < 4; i++) {
			data = qlcnic_ind_rd(adapter, qlcnic_ms_read_data[i]);
			*buffer++ = cpu_to_le32(data);
		}
		addr += 16;
		reg_read -= 16;
		ret += 16;
	}
out:
	mutex_unlock(&adapter->ahw->mem_lock);
	return mem->size;
}