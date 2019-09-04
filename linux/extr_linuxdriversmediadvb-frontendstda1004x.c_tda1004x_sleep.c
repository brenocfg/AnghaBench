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
struct tda1004x_state {int demod_type; TYPE_1__* config; } ;
struct dvb_frontend {struct tda1004x_state* demodulator_priv; } ;
struct TYPE_2__ {int gpio_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  TDA10046H_CONF_POLARITY ; 
 int /*<<< orphan*/  TDA10046H_CONF_TRISTATE1 ; 
 int TDA10046_GP00_I ; 
 int /*<<< orphan*/  TDA1004X_CONFADC1 ; 
 int /*<<< orphan*/  TDA1004X_CONFADC2 ; 
 int /*<<< orphan*/  TDA1004X_CONFC4 ; 
#define  TDA1004X_DEMOD_TDA10045 129 
#define  TDA1004X_DEMOD_TDA10046 128 
 int /*<<< orphan*/  tda1004x_write_byteI (struct tda1004x_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tda1004x_write_mask (struct tda1004x_state*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int tda1004x_sleep(struct dvb_frontend* fe)
{
	struct tda1004x_state* state = fe->demodulator_priv;
	int gpio_conf;

	switch (state->demod_type) {
	case TDA1004X_DEMOD_TDA10045:
		tda1004x_write_mask(state, TDA1004X_CONFADC1, 0x10, 0x10);
		break;

	case TDA1004X_DEMOD_TDA10046:
		/* set outputs to tristate */
		tda1004x_write_byteI(state, TDA10046H_CONF_TRISTATE1, 0xff);
		/* invert GPIO 1 and 3 if desired*/
		gpio_conf = state->config->gpio_config;
		if (gpio_conf >= TDA10046_GP00_I)
			tda1004x_write_mask(state, TDA10046H_CONF_POLARITY, 0x0f,
							(gpio_conf & 0x0f) ^ 0x0a);

		tda1004x_write_mask(state, TDA1004X_CONFADC2, 0xc0, 0xc0);
		tda1004x_write_mask(state, TDA1004X_CONFC4, 1, 1);
		break;
	}

	return 0;
}