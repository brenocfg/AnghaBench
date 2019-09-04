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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP4430_PRM_PARTITION ; 
 int /*<<< orphan*/  OMAP4430_RST_GLOBAL_WARM_SW_MASK ; 
 int /*<<< orphan*/  OMAP4_PRM_RSTCTRL_OFFSET ; 
 scalar_t__ PRM_INSTANCE_UNKNOWN ; 
 int /*<<< orphan*/  omap4_prminst_read_inst_reg (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4_prminst_write_inst_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ omap4_prmst_get_prm_dev_inst () ; 

void omap4_prminst_global_warm_sw_reset(void)
{
	u32 v;
	s32 inst = omap4_prmst_get_prm_dev_inst();

	if (inst == PRM_INSTANCE_UNKNOWN)
		return;

	v = omap4_prminst_read_inst_reg(OMAP4430_PRM_PARTITION, inst,
					OMAP4_PRM_RSTCTRL_OFFSET);
	v |= OMAP4430_RST_GLOBAL_WARM_SW_MASK;
	omap4_prminst_write_inst_reg(v, OMAP4430_PRM_PARTITION,
				 inst, OMAP4_PRM_RSTCTRL_OFFSET);

	/* OCP barrier */
	v = omap4_prminst_read_inst_reg(OMAP4430_PRM_PARTITION,
				    inst, OMAP4_PRM_RSTCTRL_OFFSET);
}