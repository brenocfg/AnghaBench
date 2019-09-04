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
struct stv0900_state {int demod; struct stv0900_internal* internal; } ;
struct stv0900_signal_info {int /*<<< orphan*/  symbol_rate; scalar_t__ locked; int /*<<< orphan*/  frequency; } ;
struct stv0900_internal {struct stv0900_signal_info* result; } ;
struct dvb_frontend {struct stv0900_state* demodulator_priv; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  symbol_rate; int /*<<< orphan*/  frequency; } ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */

__attribute__((used)) static int stv0900_get_frontend(struct dvb_frontend *fe,
				struct dtv_frontend_properties *p)
{
	struct stv0900_state *state = fe->demodulator_priv;
	struct stv0900_internal *intp = state->internal;
	enum fe_stv0900_demod_num demod = state->demod;
	struct stv0900_signal_info p_result = intp->result[demod];

	p->frequency = p_result.locked ? p_result.frequency : 0;
	p->symbol_rate = p_result.locked ? p_result.symbol_rate : 0;
	return 0;
}