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
 int ETIME ; 
 int /*<<< orphan*/  HW_ATL_FW_SM_RAM ; 
 int aq_hw_read_reg (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  aq_hw_write_reg (struct aq_hw_s*,int,int) ; 
 int hw_atl_reg_glb_cpu_sem_get (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_reg_glb_cpu_sem_set (struct aq_hw_s*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_atl_utils_fw_upload_dwords(struct aq_hw_s *self, u32 a, u32 *p,
					 u32 cnt)
{
	int err = 0;
	bool is_locked;

	is_locked = hw_atl_reg_glb_cpu_sem_get(self, HW_ATL_FW_SM_RAM);
	if (!is_locked) {
		err = -ETIME;
		goto err_exit;
	}

	aq_hw_write_reg(self, 0x00000208U, a);

	for (++cnt; --cnt;) {
		u32 i = 0U;

		aq_hw_write_reg(self, 0x0000020CU, *(p++));
		aq_hw_write_reg(self, 0x00000200U, 0xC000U);

		for (i = 1024U;
			(0x100U & aq_hw_read_reg(self, 0x00000200U)) && --i;) {
		}
	}

	hw_atl_reg_glb_cpu_sem_set(self, 1U, HW_ATL_FW_SM_RAM);

err_exit:
	return err;
}