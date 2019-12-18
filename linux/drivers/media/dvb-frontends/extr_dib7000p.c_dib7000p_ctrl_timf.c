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
typedef  int /*<<< orphan*/  u32 ;
struct dvb_frontend {struct dib7000p_state* demodulator_priv; } ;
struct dib7000p_state {int /*<<< orphan*/  timf; int /*<<< orphan*/  current_bandwidth; } ;

/* Variables and functions */
#define  DEMOD_TIMF_GET 130 
#define  DEMOD_TIMF_SET 129 
#define  DEMOD_TIMF_UPDATE 128 
 int /*<<< orphan*/  dib7000p_set_bandwidth (struct dib7000p_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000p_update_timf (struct dib7000p_state*) ; 

__attribute__((used)) static u32 dib7000p_ctrl_timf(struct dvb_frontend *fe, u8 op, u32 timf)
{
	struct dib7000p_state *state = fe->demodulator_priv;
	switch (op) {
	case DEMOD_TIMF_SET:
		state->timf = timf;
		break;
	case DEMOD_TIMF_UPDATE:
		dib7000p_update_timf(state);
		break;
	case DEMOD_TIMF_GET:
		break;
	}
	dib7000p_set_bandwidth(state, state->current_bandwidth);
	return state->timf;
}