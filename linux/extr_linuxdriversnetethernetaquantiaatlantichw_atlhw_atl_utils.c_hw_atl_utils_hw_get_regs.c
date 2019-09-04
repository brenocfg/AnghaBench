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
typedef  int /*<<< orphan*/  u32 ;
struct aq_hw_s {int dummy; } ;
struct aq_hw_caps_s {unsigned int mac_regs_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  aq_hw_read_reg (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hw_atl_utils_hw_mac_regs ; 

int hw_atl_utils_hw_get_regs(struct aq_hw_s *self,
			     const struct aq_hw_caps_s *aq_hw_caps,
			     u32 *regs_buff)
{
	unsigned int i = 0U;

	for (i = 0; i < aq_hw_caps->mac_regs_count; i++)
		regs_buff[i] = aq_hw_read_reg(self,
					      hw_atl_utils_hw_mac_regs[i]);
	return 0;
}