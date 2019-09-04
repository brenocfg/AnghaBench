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
struct dvb_pll_priv {int frequency; int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  pll_i2c_address; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  bandwidth_hz; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {struct dvb_pll_priv* tuner_priv; struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 int EINVAL ; 
 int dvb_pll_configure (struct dvb_frontend*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dvb_pll_calc_regs(struct dvb_frontend *fe,
			     u8 *buf, int buf_len)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct dvb_pll_priv *priv = fe->tuner_priv;
	int result;
	u32 frequency = 0;

	if (buf_len < 5)
		return -EINVAL;

	result = dvb_pll_configure(fe, buf + 1, c->frequency);
	if (result < 0)
		return result;
	else
		frequency = result;

	buf[0] = priv->pll_i2c_address;

	priv->frequency = frequency;
	priv->bandwidth = c->bandwidth_hz;

	return 5;
}