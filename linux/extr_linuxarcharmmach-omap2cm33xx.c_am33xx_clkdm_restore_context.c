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
struct clockdomain {int context; } ;

/* Variables and functions */
#define  OMAP34XX_CLKSTCTRL_DISABLE_AUTO 131 
#define  OMAP34XX_CLKSTCTRL_ENABLE_AUTO 130 
#define  OMAP34XX_CLKSTCTRL_FORCE_SLEEP 129 
#define  OMAP34XX_CLKSTCTRL_FORCE_WAKEUP 128 
 int /*<<< orphan*/  am33xx_clkdm_allow_idle (struct clockdomain*) ; 
 int /*<<< orphan*/  am33xx_clkdm_deny_idle (struct clockdomain*) ; 
 int /*<<< orphan*/  am33xx_clkdm_sleep (struct clockdomain*) ; 
 int /*<<< orphan*/  am33xx_clkdm_wakeup (struct clockdomain*) ; 

__attribute__((used)) static int am33xx_clkdm_restore_context(struct clockdomain *clkdm)
{
	switch (clkdm->context) {
	case OMAP34XX_CLKSTCTRL_DISABLE_AUTO:
		am33xx_clkdm_deny_idle(clkdm);
		break;
	case OMAP34XX_CLKSTCTRL_FORCE_SLEEP:
		am33xx_clkdm_sleep(clkdm);
		break;
	case OMAP34XX_CLKSTCTRL_FORCE_WAKEUP:
		am33xx_clkdm_wakeup(clkdm);
		break;
	case OMAP34XX_CLKSTCTRL_ENABLE_AUTO:
		am33xx_clkdm_allow_idle(clkdm);
		break;
	}
	return 0;
}