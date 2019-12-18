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
typedef  int u8 ;
struct lgs8gxx_state {TYPE_1__* config; } ;
struct dvb_frontend {struct lgs8gxx_state* demodulator_priv; } ;
struct TYPE_2__ {int tuner_address; } ;

/* Variables and functions */
 int lgs8gxx_write_reg (struct lgs8gxx_state*,int,int) ; 

__attribute__((used)) static int lgs8gxx_i2c_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct lgs8gxx_state *priv = fe->demodulator_priv;

	if (priv->config->tuner_address == 0)
		return 0;
	if (enable) {
		u8 v = 0x80 | priv->config->tuner_address;
		return lgs8gxx_write_reg(priv, 0x01, v);
	}
	return lgs8gxx_write_reg(priv, 0x01, 0);
}