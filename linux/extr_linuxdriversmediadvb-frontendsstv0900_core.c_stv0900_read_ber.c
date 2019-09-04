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
typedef  int /*<<< orphan*/  u32 ;
struct stv0900_state {int /*<<< orphan*/  demod; struct stv0900_internal* internal; } ;
struct stv0900_internal {int dummy; } ;
struct dvb_frontend {struct stv0900_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  stv0900_get_ber (struct stv0900_internal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv0900_read_ber(struct dvb_frontend *fe, u32 *ber)
{
	struct stv0900_state *state = fe->demodulator_priv;
	struct stv0900_internal *internal = state->internal;

	*ber = stv0900_get_ber(internal, state->demod);

	return 0;
}