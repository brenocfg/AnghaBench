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
 int /*<<< orphan*/  OMAP24XX_AUTO_96M_MASK ; 
 int /*<<< orphan*/  OMAP2XXX_APLL_AUTOIDLE_DISABLE ; 
 int /*<<< orphan*/  _omap2xxx_set_apll_autoidle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap2xxx_cm_set_apll96_auto_low_power_stop(void)
{
	_omap2xxx_set_apll_autoidle(OMAP2XXX_APLL_AUTOIDLE_DISABLE,
				    OMAP24XX_AUTO_96M_MASK);
}