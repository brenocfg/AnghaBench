#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct tuner_simple_priv {scalar_t__ bandwidth; scalar_t__ frequency; TYPE_1__ i2c_props; } ;
struct dtv_frontend_properties {scalar_t__ delivery_system; scalar_t__ bandwidth_hz; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {struct tuner_simple_priv* tuner_priv; struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ simple_dvb_configure (struct dvb_frontend*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int simple_dvb_calc_regs(struct dvb_frontend *fe,
				u8 *buf, int buf_len)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 delsys = c->delivery_system;
	u32 bw = c->bandwidth_hz;
	struct tuner_simple_priv *priv = fe->tuner_priv;
	u32 frequency;

	if (buf_len < 5)
		return -EINVAL;

	frequency = simple_dvb_configure(fe, buf+1, delsys, c->frequency, bw);
	if (frequency == 0)
		return -EINVAL;

	buf[0] = priv->i2c_props.addr;

	priv->frequency = frequency;
	priv->bandwidth = c->bandwidth_hz;

	return 5;
}