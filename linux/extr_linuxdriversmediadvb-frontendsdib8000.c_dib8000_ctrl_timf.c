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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dib8000_state {int /*<<< orphan*/  timf; int /*<<< orphan*/ * fe; } ;

/* Variables and functions */
#define  DEMOD_TIMF_GET 130 
#define  DEMOD_TIMF_SET 129 
#define  DEMOD_TIMF_UPDATE 128 
 int /*<<< orphan*/  dib8000_set_bandwidth (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dib8000_update_timf (struct dib8000_state*) ; 

__attribute__((used)) static u32 dib8000_ctrl_timf(struct dvb_frontend *fe, uint8_t op, uint32_t timf)
{
	struct dib8000_state *state = fe->demodulator_priv;

	switch (op) {
	case DEMOD_TIMF_SET:
			state->timf = timf;
			break;
	case DEMOD_TIMF_UPDATE:
			dib8000_update_timf(state);
			break;
	case DEMOD_TIMF_GET:
			break;
	}
	dib8000_set_bandwidth(state->fe[0], 6000);

	return state->timf;
}