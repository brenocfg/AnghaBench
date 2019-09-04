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
struct powerdomain {int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_POWERSTATE_MASK ; 
 int /*<<< orphan*/  TI81XX_PM_PWSTCTRL ; 
 int omap2_prm_read_mod_bits_shift (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti81xx_pwrdm_read_next_pwrst(struct powerdomain *pwrdm)
{
	return omap2_prm_read_mod_bits_shift(pwrdm->prcm_offs,
					     TI81XX_PM_PWSTCTRL,
					     OMAP_POWERSTATE_MASK);
}