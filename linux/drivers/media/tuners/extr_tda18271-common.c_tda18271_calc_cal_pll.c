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
typedef  int u32 ;
struct tda18271_priv {unsigned char* tda18271_regs; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAL_PLL ; 
 size_t R_CD1 ; 
 size_t R_CD2 ; 
 size_t R_CD3 ; 
 size_t R_CPD ; 
 int tda18271_lookup_pll_map (struct dvb_frontend*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 scalar_t__ tda_fail (int) ; 

int tda18271_calc_cal_pll(struct dvb_frontend *fe, u32 freq)
{
	/* sets cal post divider & divider bytes, but does not write them */
	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned char *regs = priv->tda18271_regs;
	u8 d, pd;
	u32 div;

	int ret = tda18271_lookup_pll_map(fe, CAL_PLL, &freq, &pd, &d);
	if (tda_fail(ret))
		goto fail;

	regs[R_CPD]   = pd;

	div =  ((d * (freq / 1000)) << 7) / 125;

	regs[R_CD1]   = 0x7f & (div >> 16);
	regs[R_CD2]   = 0xff & (div >> 8);
	regs[R_CD3]   = 0xff & div;
fail:
	return ret;
}