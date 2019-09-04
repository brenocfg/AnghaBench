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
 int REBOOT_SOFT ; 
 int /*<<< orphan*/  soft_restart (int /*<<< orphan*/ ) ; 

void spear_restart(enum reboot_mode mode, const char *cmd)
{
	if (mode == REBOOT_SOFT) {
		/* software reset, Jump into ROM at address 0 */
		soft_restart(0);
	} else {
		/* hardware reset, Use on-chip reset capability */
#ifdef CONFIG_ARCH_SPEAR13XX
		writel_relaxed(0x01, SPEAR13XX_SYS_SW_RES);
#endif
#if defined(CONFIG_ARCH_SPEAR3XX) || defined(CONFIG_ARCH_SPEAR6XX)
		sysctl_soft_reset((void __iomem *)VA_SPEAR_SYS_CTRL_BASE);
#endif
	}
}