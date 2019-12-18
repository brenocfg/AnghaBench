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

/* Variables and functions */
 int /*<<< orphan*/  HW_ATL_RPO_OUTER_VL_INS_MODE_ADR ; 
 int /*<<< orphan*/  HW_ATL_RPO_OUTER_VL_INS_MODE_MSK ; 
 int /*<<< orphan*/  HW_ATL_RPO_OUTER_VL_INS_MODE_SHIFT ; 
 int /*<<< orphan*/  aq_hw_write_reg_bit (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hw_atl_rpo_outer_vlan_tag_mode_set(void *context,
					u32 outervlantagmode)
{
	aq_hw_write_reg_bit(context, HW_ATL_RPO_OUTER_VL_INS_MODE_ADR,
			    HW_ATL_RPO_OUTER_VL_INS_MODE_MSK,
			    HW_ATL_RPO_OUTER_VL_INS_MODE_SHIFT,
			    outervlantagmode);
}