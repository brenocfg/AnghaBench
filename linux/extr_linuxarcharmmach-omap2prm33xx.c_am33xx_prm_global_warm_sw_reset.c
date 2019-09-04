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

/* Variables and functions */
 int /*<<< orphan*/  AM33XX_PRM_DEVICE_MOD ; 
 int /*<<< orphan*/  AM33XX_PRM_RSTCTRL_OFFSET ; 
 int /*<<< orphan*/  AM33XX_RST_GLOBAL_WARM_SW_MASK ; 
 int /*<<< orphan*/  am33xx_prm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  am33xx_prm_rmw_reg_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void am33xx_prm_global_warm_sw_reset(void)
{
	am33xx_prm_rmw_reg_bits(AM33XX_RST_GLOBAL_WARM_SW_MASK,
				AM33XX_RST_GLOBAL_WARM_SW_MASK,
				AM33XX_PRM_DEVICE_MOD,
				AM33XX_PRM_RSTCTRL_OFFSET);

	/* OCP barrier */
	(void)am33xx_prm_read_reg(AM33XX_PRM_DEVICE_MOD,
				  AM33XX_PRM_RSTCTRL_OFFSET);
}