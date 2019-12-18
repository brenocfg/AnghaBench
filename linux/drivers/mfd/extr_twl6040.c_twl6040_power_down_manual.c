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
struct twl6040 {int dummy; } ;

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
 int twl6040_reg_read (struct twl6040*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6040_reg_write (struct twl6040*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void twl6040_power_down_manual(struct twl6040 *twl6040)
{
	u8 ncpctl, ldoctl, lppllctl;

	ncpctl = twl6040_reg_read(twl6040, TWL6040_REG_NCPCTL);
	ldoctl = twl6040_reg_read(twl6040, TWL6040_REG_LDOCTL);
	lppllctl = twl6040_reg_read(twl6040, TWL6040_REG_LPPLLCTL);

	/* enable internal oscillator */
	ldoctl |= TWL6040_OSCENA;
	twl6040_reg_write(twl6040, TWL6040_REG_LDOCTL, ldoctl);
	usleep_range(1000, 1500);

	/* disable low-power PLL */
	lppllctl &= ~TWL6040_LPLLENA;
	twl6040_reg_write(twl6040, TWL6040_REG_LPPLLCTL, lppllctl);

	/* disable low-side LDO */
	ldoctl &= ~TWL6040_LSLDOENA;
	twl6040_reg_write(twl6040, TWL6040_REG_LDOCTL, ldoctl);

	/* disable negative charge pump */
	ncpctl &= ~TWL6040_NCPENA;
	twl6040_reg_write(twl6040, TWL6040_REG_NCPCTL, ncpctl);

	/* disable high-side LDO, reference system and internal oscillator */
	ldoctl &= ~(TWL6040_HSLDOENA | TWL6040_REFENA | TWL6040_OSCENA);
	twl6040_reg_write(twl6040, TWL6040_REG_LDOCTL, ldoctl);
}