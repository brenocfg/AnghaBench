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
struct tda_state {struct i2c_adapter* i2c; int /*<<< orphan*/  adr; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {TYPE_1__ ops; struct tda_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  InitCal (struct tda_state*) ; 
 struct tda_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reset (struct tda_state*) ; 
 int /*<<< orphan*/  tuner_ops ; 

struct dvb_frontend *tda18271c2dd_attach(struct dvb_frontend *fe,
					 struct i2c_adapter *i2c, u8 adr)
{
	struct tda_state *state;

	state = kzalloc(sizeof(struct tda_state), GFP_KERNEL);
	if (!state)
		return NULL;

	fe->tuner_priv = state;
	state->adr = adr;
	state->i2c = i2c;
	memcpy(&fe->ops.tuner_ops, &tuner_ops, sizeof(struct dvb_tuner_ops));
	reset(state);
	InitCal(state);

	return fe;
}