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
typedef  int u8 ;
struct powerdomain {int /*<<< orphan*/  prcm_offs; } ;

/* Variables and functions */
 int EINVAL ; 
 int OMAP24XX_PWRDM_POWER_OFF ; 
 int OMAP24XX_PWRDM_POWER_ON ; 
 int OMAP24XX_PWRDM_POWER_RET ; 
 int /*<<< orphan*/  OMAP2_PM_PWSTCTRL ; 
 int /*<<< orphan*/  OMAP_POWERSTATE_MASK ; 
 int OMAP_POWERSTATE_SHIFT ; 
#define  PWRDM_POWER_OFF 130 
#define  PWRDM_POWER_ON 129 
#define  PWRDM_POWER_RET 128 
 int /*<<< orphan*/  omap2_prm_rmw_mod_reg_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap2xxx_pwrdm_set_next_pwrst(struct powerdomain *pwrdm, u8 pwrst)
{
	u8 omap24xx_pwrst;

	switch (pwrst) {
	case PWRDM_POWER_OFF:
		omap24xx_pwrst = OMAP24XX_PWRDM_POWER_OFF;
		break;
	case PWRDM_POWER_RET:
		omap24xx_pwrst = OMAP24XX_PWRDM_POWER_RET;
		break;
	case PWRDM_POWER_ON:
		omap24xx_pwrst = OMAP24XX_PWRDM_POWER_ON;
		break;
	default:
		return -EINVAL;
	}

	omap2_prm_rmw_mod_reg_bits(OMAP_POWERSTATE_MASK,
				   (omap24xx_pwrst << OMAP_POWERSTATE_SHIFT),
				   pwrdm->prcm_offs, OMAP2_PM_PWSTCTRL);
	return 0;
}