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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct stv6110_priv {int* regs; int mclk; } ;
struct dvb_frontend {struct stv6110_priv* tuner_priv; } ;

/* Variables and functions */
 size_t RSTV6110_TUNING1 ; 
 size_t RSTV6110_TUNING2 ; 
 int /*<<< orphan*/  stv6110_read_regs (struct dvb_frontend*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stv6110_get_frequency(struct dvb_frontend *fe, u32 *frequency)
{
	struct stv6110_priv *priv = fe->tuner_priv;
	u32 nbsteps, divider, psd2, freq;
	u8 regs[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	stv6110_read_regs(fe, regs, 0, 8);
	/*N*/
	divider = (priv->regs[RSTV6110_TUNING2] & 0x0f) << 8;
	divider += priv->regs[RSTV6110_TUNING1];

	/*R*/
	nbsteps  = (priv->regs[RSTV6110_TUNING2] >> 6) & 3;
	/*p*/
	psd2  = (priv->regs[RSTV6110_TUNING2] >> 4) & 1;

	freq = divider * (priv->mclk / 1000);
	freq /= (1 << (nbsteps + psd2));
	freq /= 4;

	*frequency = freq;

	return 0;
}