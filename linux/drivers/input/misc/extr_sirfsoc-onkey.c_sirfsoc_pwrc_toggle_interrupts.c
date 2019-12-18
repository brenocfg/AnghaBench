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
struct sirfsoc_pwrc_drvdata {scalar_t__ pwrc_base; } ;

/* Variables and functions */
 scalar_t__ PWRC_INT_MASK ; 
 int /*<<< orphan*/  PWRC_ON_KEY_BIT ; 
 int /*<<< orphan*/  sirfsoc_rtc_iobrg_readl (scalar_t__) ; 
 int /*<<< orphan*/  sirfsoc_rtc_iobrg_writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sirfsoc_pwrc_toggle_interrupts(struct sirfsoc_pwrc_drvdata *pwrcdrv,
					   bool enable)
{
	u32 int_mask;

	int_mask = sirfsoc_rtc_iobrg_readl(pwrcdrv->pwrc_base + PWRC_INT_MASK);
	if (enable)
		int_mask |= PWRC_ON_KEY_BIT;
	else
		int_mask &= ~PWRC_ON_KEY_BIT;
	sirfsoc_rtc_iobrg_writel(int_mask, pwrcdrv->pwrc_base + PWRC_INT_MASK);
}