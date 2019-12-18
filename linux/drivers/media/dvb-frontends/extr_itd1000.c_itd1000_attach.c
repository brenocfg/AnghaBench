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
struct itd1000_state {void** shadow; struct i2c_adapter* i2c; struct itd1000_config* cfg; } ;
struct itd1000_config {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {struct itd1000_state* tuner_priv; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* itd1000_read_reg (struct itd1000_state*,int) ; 
 int /*<<< orphan*/  itd1000_tuner_ops ; 
 int /*<<< orphan*/  itd_info (char*,int) ; 
 int /*<<< orphan*/  kfree (struct itd1000_state*) ; 
 struct itd1000_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (void**,int,int) ; 

struct dvb_frontend *itd1000_attach(struct dvb_frontend *fe, struct i2c_adapter *i2c, struct itd1000_config *cfg)
{
	struct itd1000_state *state = NULL;
	u8 i = 0;

	state = kzalloc(sizeof(struct itd1000_state), GFP_KERNEL);
	if (state == NULL)
		return NULL;

	state->cfg = cfg;
	state->i2c = i2c;

	i = itd1000_read_reg(state, 0);
	if (i != 0) {
		kfree(state);
		return NULL;
	}
	itd_info("successfully identified (ID: %d)\n", i);

	memset(state->shadow, 0xff, sizeof(state->shadow));
	for (i = 0x65; i < 0x9c; i++)
		state->shadow[i] = itd1000_read_reg(state, i);

	memcpy(&fe->ops.tuner_ops, &itd1000_tuner_ops, sizeof(struct dvb_tuner_ops));

	fe->tuner_priv = state;

	return fe;
}