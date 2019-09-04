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
typedef  int /*<<< orphan*/  u32 ;
struct tda18271_priv {unsigned char* tda18271_regs; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IR_MEASURE ; 
 size_t R_EP5 ; 
 int tda18271_lookup_map (struct dvb_frontend*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ tda_fail (int) ; 

int tda18271_calc_ir_measure(struct dvb_frontend *fe, u32 *freq)
{
	/* sets IR Meas bits, but does not write them */
	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned char *regs = priv->tda18271_regs;
	u8 val;

	int ret = tda18271_lookup_map(fe, IR_MEASURE, freq, &val);
	if (tda_fail(ret))
		goto fail;

	regs[R_EP5] &= ~0x07;
	regs[R_EP5] |= (0x07 & val);
fail:
	return ret;
}