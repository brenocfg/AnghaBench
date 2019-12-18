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
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_rpf_vlan_prom_mode_en_set (struct aq_hw_s*,int) ; 

__attribute__((used)) static int hw_atl_b0_hw_vlan_ctrl(struct aq_hw_s *self, bool enable)
{
	/* set promisc in case of disabing the vland filter */
	hw_atl_rpf_vlan_prom_mode_en_set(self, !enable);

	return aq_hw_err_from_flags(self);
}