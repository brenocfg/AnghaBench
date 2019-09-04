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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum reboot_mode { ____Placeholder_reboot_mode } reboot_mode ;

/* Variables and functions */
 int /*<<< orphan*/  omap3_ctrl_write_boot_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_prm_reset_system () ; 

void omap3xxx_restart(enum reboot_mode mode, const char *cmd)
{
	omap3_ctrl_write_boot_mode((cmd ? (u8)*cmd : 0));
	omap_prm_reset_system();
}