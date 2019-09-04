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
struct aq_hw_s {unsigned int mbox_addr; } ;
struct aq_hw_caps_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_HW_WAIT_FOR (int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  HW_ATL_UCP_0X370_REG ; 
 unsigned int aq_hw_read_reg (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  aq_hw_write_reg (struct aq_hw_s*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  get_random_bytes (unsigned int*,int) ; 
 int /*<<< orphan*/  hw_atl_reg_glb_cpu_scratch_scp_set (struct aq_hw_s*,int,unsigned int) ; 

__attribute__((used)) static int hw_atl_utils_init_ucp(struct aq_hw_s *self,
				 const struct aq_hw_caps_s *aq_hw_caps)
{
	int err = 0;

	if (!aq_hw_read_reg(self, 0x370U)) {
		unsigned int rnd = 0U;
		unsigned int ucp_0x370 = 0U;

		get_random_bytes(&rnd, sizeof(unsigned int));

		ucp_0x370 = 0x02020202U | (0xFEFEFEFEU & rnd);
		aq_hw_write_reg(self, HW_ATL_UCP_0X370_REG, ucp_0x370);
	}

	hw_atl_reg_glb_cpu_scratch_scp_set(self, 0x00000000U, 25U);

	/* check 10 times by 1ms */
	AQ_HW_WAIT_FOR(0U != (self->mbox_addr =
			aq_hw_read_reg(self, 0x360U)), 1000U, 10U);

	return err;
}