#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_HW_WAIT_FOR (int,int,unsigned int) ; 
 int ETIME ; 
 int /*<<< orphan*/  HW_ATL_FW_SM_RAM ; 
 int /*<<< orphan*/  HW_ATL_MIF_ADDR ; 
 int /*<<< orphan*/  HW_ATL_MIF_CMD ; 
 int /*<<< orphan*/  HW_ATL_MIF_VAL ; 
 scalar_t__ IS_CHIP_FEATURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REVISION_B1 ; 
 int aq_hw_read_reg (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aq_hw_write_reg (struct aq_hw_s*,int /*<<< orphan*/ ,int) ; 
 unsigned int hw_atl_reg_glb_cpu_sem_get (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_reg_glb_cpu_sem_set (struct aq_hw_s*,unsigned int,int /*<<< orphan*/ ) ; 

int hw_atl_utils_fw_downld_dwords(struct aq_hw_s *self, u32 a,
				  u32 *p, u32 cnt)
{
	int err = 0;

	AQ_HW_WAIT_FOR(hw_atl_reg_glb_cpu_sem_get(self,
						  HW_ATL_FW_SM_RAM) == 1U,
						  1U, 10000U);

	if (err < 0) {
		bool is_locked;

		hw_atl_reg_glb_cpu_sem_set(self, 1U, HW_ATL_FW_SM_RAM);
		is_locked = hw_atl_reg_glb_cpu_sem_get(self, HW_ATL_FW_SM_RAM);
		if (!is_locked) {
			err = -ETIME;
			goto err_exit;
		}
	}

	aq_hw_write_reg(self, HW_ATL_MIF_ADDR, a);

	for (++cnt; --cnt && !err;) {
		aq_hw_write_reg(self, HW_ATL_MIF_CMD, 0x00008000U);

		if (IS_CHIP_FEATURE(REVISION_B1))
			AQ_HW_WAIT_FOR(a != aq_hw_read_reg(self,
							   HW_ATL_MIF_ADDR),
				       1, 1000U);
		else
			AQ_HW_WAIT_FOR(!(0x100 & aq_hw_read_reg(self,
							   HW_ATL_MIF_CMD)),
				       1, 1000U);

		*(p++) = aq_hw_read_reg(self, HW_ATL_MIF_VAL);
		a += 4;
	}

	hw_atl_reg_glb_cpu_sem_set(self, 1U, HW_ATL_FW_SM_RAM);

err_exit:
	return err;
}