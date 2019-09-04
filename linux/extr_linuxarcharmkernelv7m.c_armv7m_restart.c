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
 scalar_t__ BASEADDR_V7M_SCB ; 
 scalar_t__ V7M_SCB_AIRCR ; 
 int V7M_SCB_AIRCR_SYSRESETREQ ; 
 int V7M_SCB_AIRCR_VECTKEY ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  dsb () ; 

void armv7m_restart(enum reboot_mode mode, const char *cmd)
{
	dsb();
	__raw_writel(V7M_SCB_AIRCR_VECTKEY | V7M_SCB_AIRCR_SYSRESETREQ,
			BASEADDR_V7M_SCB + V7M_SCB_AIRCR);
	dsb();
}