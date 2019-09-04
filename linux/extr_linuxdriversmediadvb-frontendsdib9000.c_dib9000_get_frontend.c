#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct dvb_frontend {struct dib9000_state* demodulator_priv; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  rolloff; int /*<<< orphan*/  code_rate_LP; int /*<<< orphan*/  code_rate_HP; int /*<<< orphan*/  hierarchy; int /*<<< orphan*/  modulation; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  inversion; } ;
struct dib9000_state {scalar_t__ get_frontend_internal; int /*<<< orphan*/  demod_lock; TYPE_3__** fe; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_6__ {int /*<<< orphan*/  rolloff; int /*<<< orphan*/  code_rate_LP; int /*<<< orphan*/  code_rate_HP; int /*<<< orphan*/  hierarchy; int /*<<< orphan*/  modulation; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  inversion; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_frontend ) (TYPE_3__*,struct dtv_frontend_properties*) ;int /*<<< orphan*/  (* read_status ) (TYPE_3__*,int*) ;} ;
struct TYPE_7__ {TYPE_2__ dtv_property_cache; TYPE_1__ ops; } ;

/* Variables and functions */
 int EINTR ; 
 int FE_HAS_SYNC ; 
 size_t MAX_NUMBER_OF_FRONTENDS ; 
 int dib9000_fw_get_channel (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,struct dtv_frontend_properties*) ; 

__attribute__((used)) static int dib9000_get_frontend(struct dvb_frontend *fe,
				struct dtv_frontend_properties *c)
{
	struct dib9000_state *state = fe->demodulator_priv;
	u8 index_frontend, sub_index_frontend;
	enum fe_status stat;
	int ret = 0;

	if (state->get_frontend_internal == 0) {
		if (mutex_lock_interruptible(&state->demod_lock) < 0) {
			dprintk("could not get the lock\n");
			return -EINTR;
		}
	}

	for (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != NULL); index_frontend++) {
		state->fe[index_frontend]->ops.read_status(state->fe[index_frontend], &stat);
		if (stat & FE_HAS_SYNC) {
			dprintk("TPS lock on the slave%i\n", index_frontend);

			/* synchronize the cache with the other frontends */
			state->fe[index_frontend]->ops.get_frontend(state->fe[index_frontend], c);
			for (sub_index_frontend = 0; (sub_index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[sub_index_frontend] != NULL);
			     sub_index_frontend++) {
				if (sub_index_frontend != index_frontend) {
					state->fe[sub_index_frontend]->dtv_property_cache.modulation =
					    state->fe[index_frontend]->dtv_property_cache.modulation;
					state->fe[sub_index_frontend]->dtv_property_cache.inversion =
					    state->fe[index_frontend]->dtv_property_cache.inversion;
					state->fe[sub_index_frontend]->dtv_property_cache.transmission_mode =
					    state->fe[index_frontend]->dtv_property_cache.transmission_mode;
					state->fe[sub_index_frontend]->dtv_property_cache.guard_interval =
					    state->fe[index_frontend]->dtv_property_cache.guard_interval;
					state->fe[sub_index_frontend]->dtv_property_cache.hierarchy =
					    state->fe[index_frontend]->dtv_property_cache.hierarchy;
					state->fe[sub_index_frontend]->dtv_property_cache.code_rate_HP =
					    state->fe[index_frontend]->dtv_property_cache.code_rate_HP;
					state->fe[sub_index_frontend]->dtv_property_cache.code_rate_LP =
					    state->fe[index_frontend]->dtv_property_cache.code_rate_LP;
					state->fe[sub_index_frontend]->dtv_property_cache.rolloff =
					    state->fe[index_frontend]->dtv_property_cache.rolloff;
				}
			}
			ret = 0;
			goto return_value;
		}
	}

	/* get the channel from master chip */
	ret = dib9000_fw_get_channel(fe);
	if (ret != 0)
		goto return_value;

	/* synchronize the cache with the other frontends */
	for (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != NULL); index_frontend++) {
		state->fe[index_frontend]->dtv_property_cache.inversion = c->inversion;
		state->fe[index_frontend]->dtv_property_cache.transmission_mode = c->transmission_mode;
		state->fe[index_frontend]->dtv_property_cache.guard_interval = c->guard_interval;
		state->fe[index_frontend]->dtv_property_cache.modulation = c->modulation;
		state->fe[index_frontend]->dtv_property_cache.hierarchy = c->hierarchy;
		state->fe[index_frontend]->dtv_property_cache.code_rate_HP = c->code_rate_HP;
		state->fe[index_frontend]->dtv_property_cache.code_rate_LP = c->code_rate_LP;
		state->fe[index_frontend]->dtv_property_cache.rolloff = c->rolloff;
	}
	ret = 0;

return_value:
	if (state->get_frontend_internal == 0)
		mutex_unlock(&state->demod_lock);
	return ret;
}