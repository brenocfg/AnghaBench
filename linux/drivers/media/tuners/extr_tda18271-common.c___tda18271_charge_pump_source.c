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
struct tda18271_priv {unsigned char* tda18271_regs; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;
typedef  enum tda18271_pll { ____Placeholder_tda18271_pll } tda18271_pll ;

/* Variables and functions */
 int R_EB4 ; 
 int R_EB7 ; 
 int TDA18271_CAL_PLL ; 
 int __tda18271_write_regs (struct dvb_frontend*,int,int,int) ; 

__attribute__((used)) static int __tda18271_charge_pump_source(struct dvb_frontend *fe,
					 enum tda18271_pll pll, int force,
					 bool lock_i2c)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned char *regs = priv->tda18271_regs;

	int r_cp = (pll == TDA18271_CAL_PLL) ? R_EB7 : R_EB4;

	regs[r_cp] &= ~0x20;
	regs[r_cp] |= ((force & 1) << 5);

	return __tda18271_write_regs(fe, r_cp, 1, lock_i2c);
}