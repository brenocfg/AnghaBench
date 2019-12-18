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
struct twl6040 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TWL6040_HSLDOENA ; 
 int TWL6040_LPLLENA ; 
 int TWL6040_LSLDOENA ; 
 int TWL6040_NCPENA ; 
 int TWL6040_OSCENA ; 
 int TWL6040_REFENA ; 
 int /*<<< orphan*/  TWL6040_REG_LDOCTL ; 
 int /*<<< orphan*/  TWL6040_REG_LPPLLCTL ; 
 int /*<<< orphan*/  TWL6040_REG_NCPCTL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int twl6040_reg_write (struct twl6040*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int twl6040_power_up_manual(struct twl6040 *twl6040)
{
	u8 ldoctl, ncpctl, lppllctl;
	int ret;

	/* enable high-side LDO, reference system and internal oscillator */
	ldoctl = TWL6040_HSLDOENA | TWL6040_REFENA | TWL6040_OSCENA;
	ret = twl6040_reg_write(twl6040, TWL6040_REG_LDOCTL, ldoctl);
	if (ret)
		return ret;
	usleep_range(10000, 10500);

	/* enable negative charge pump */
	ncpctl = TWL6040_NCPENA;
	ret = twl6040_reg_write(twl6040, TWL6040_REG_NCPCTL, ncpctl);
	if (ret)
		goto ncp_err;
	usleep_range(1000, 1500);

	/* enable low-side LDO */
	ldoctl |= TWL6040_LSLDOENA;
	ret = twl6040_reg_write(twl6040, TWL6040_REG_LDOCTL, ldoctl);
	if (ret)
		goto lsldo_err;
	usleep_range(1000, 1500);

	/* enable low-power PLL */
	lppllctl = TWL6040_LPLLENA;
	ret = twl6040_reg_write(twl6040, TWL6040_REG_LPPLLCTL, lppllctl);
	if (ret)
		goto lppll_err;
	usleep_range(5000, 5500);

	/* disable internal oscillator */
	ldoctl &= ~TWL6040_OSCENA;
	ret = twl6040_reg_write(twl6040, TWL6040_REG_LDOCTL, ldoctl);
	if (ret)
		goto osc_err;

	return 0;

osc_err:
	lppllctl &= ~TWL6040_LPLLENA;
	twl6040_reg_write(twl6040, TWL6040_REG_LPPLLCTL, lppllctl);
lppll_err:
	ldoctl &= ~TWL6040_LSLDOENA;
	twl6040_reg_write(twl6040, TWL6040_REG_LDOCTL, ldoctl);
lsldo_err:
	ncpctl &= ~TWL6040_NCPENA;
	twl6040_reg_write(twl6040, TWL6040_REG_NCPCTL, ncpctl);
ncp_err:
	ldoctl &= ~(TWL6040_HSLDOENA | TWL6040_REFENA | TWL6040_OSCENA);
	twl6040_reg_write(twl6040, TWL6040_REG_LDOCTL, ldoctl);

	dev_err(twl6040->dev, "manual power-up failed\n");
	return ret;
}