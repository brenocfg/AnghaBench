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
typedef  enum reboot_mode { ____Placeholder_reboot_mode } reboot_mode ;

/* Variables and functions */
 int /*<<< orphan*/  TI81XX_GLOBAL_RST_COLD ; 
 int /*<<< orphan*/  TI81XX_PRM_DEVICE_RSTCTRL ; 
 int /*<<< orphan*/  omap2_prm_set_mod_reg_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ti81xx_restart(enum reboot_mode mode, const char *cmd)
{
	omap2_prm_set_mod_reg_bits(TI81XX_GLOBAL_RST_COLD, 0,
				   TI81XX_PRM_DEVICE_RSTCTRL);
	while (1);
}