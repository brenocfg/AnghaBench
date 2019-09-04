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

/* Variables and functions */
 size_t R_EP1 ; 
 int tda18271_init_regs (struct dvb_frontend*) ; 
 int tda18271_read_regs (struct dvb_frontend*) ; 
 scalar_t__ tda_fail (int) ; 

__attribute__((used)) static int tda18271_ir_cal_init(struct dvb_frontend *fe)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned char *regs = priv->tda18271_regs;
	int ret;

	ret = tda18271_read_regs(fe);
	if (tda_fail(ret))
		goto fail;

	/* test IR_CAL_OK to see if we need init */
	if ((regs[R_EP1] & 0x08) == 0)
		ret = tda18271_init_regs(fe);
fail:
	return ret;
}