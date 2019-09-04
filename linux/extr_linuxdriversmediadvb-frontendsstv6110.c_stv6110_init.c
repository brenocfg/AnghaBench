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
struct stv6110_priv {int* regs; int mclk; int clk_div; } ;
struct dvb_frontend {struct stv6110_priv* tuner_priv; } ;

/* Variables and functions */
 size_t RSTV6110_CTRL1 ; 
 size_t RSTV6110_CTRL2 ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stv6110_set_bandwidth (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stv6110_write_regs (struct dvb_frontend*,int*,size_t,int) ; 

__attribute__((used)) static int stv6110_init(struct dvb_frontend *fe)
{
	struct stv6110_priv *priv = fe->tuner_priv;
	u8 buf0[] = { 0x07, 0x11, 0xdc, 0x85, 0x17, 0x01, 0xe6, 0x1e };

	memcpy(priv->regs, buf0, 8);
	/* K = (Reference / 1000000) - 16 */
	priv->regs[RSTV6110_CTRL1] &= ~(0x1f << 3);
	priv->regs[RSTV6110_CTRL1] |=
				((((priv->mclk / 1000000) - 16) & 0x1f) << 3);

	/* divisor value for the output clock */
	priv->regs[RSTV6110_CTRL2] &= ~0xc0;
	priv->regs[RSTV6110_CTRL2] |= (priv->clk_div << 6);

	stv6110_write_regs(fe, &priv->regs[RSTV6110_CTRL1], RSTV6110_CTRL1, 8);
	msleep(1);
	stv6110_set_bandwidth(fe, 72000000);

	return 0;
}