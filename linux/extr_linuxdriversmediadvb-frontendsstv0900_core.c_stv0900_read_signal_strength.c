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
typedef  int u16 ;
struct stv0900_state {int /*<<< orphan*/  demod; struct stv0900_internal* internal; } ;
struct stv0900_internal {int dummy; } ;
struct dvb_frontend {struct stv0900_state* demodulator_priv; } ;
typedef  int s32 ;

/* Variables and functions */
 int stv0900_get_rf_level (struct stv0900_internal*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv0900_rf ; 

__attribute__((used)) static int stv0900_read_signal_strength(struct dvb_frontend *fe, u16 *strength)
{
	struct stv0900_state *state = fe->demodulator_priv;
	struct stv0900_internal *internal = state->internal;
	s32 rflevel = stv0900_get_rf_level(internal, &stv0900_rf,
								state->demod);

	rflevel = (rflevel + 100) * (65535 / 70);
	if (rflevel < 0)
		rflevel = 0;

	if (rflevel > 65535)
		rflevel = 65535;

	*strength = rflevel;

	return 0;
}