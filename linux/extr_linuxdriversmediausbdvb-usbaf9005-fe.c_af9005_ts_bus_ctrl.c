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
struct dvb_frontend {struct af9005_fe_state* demodulator_priv; } ;
struct af9005_fe_state {int /*<<< orphan*/  d; int /*<<< orphan*/  opened; } ;

/* Variables and functions */
 int /*<<< orphan*/  af9005_led_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int af9005_ts_bus_ctrl(struct dvb_frontend *fe, int acquire)
{
	struct af9005_fe_state *state = fe->demodulator_priv;

	if (acquire) {
		state->opened++;
	} else {

		state->opened--;
		if (!state->opened)
			af9005_led_control(state->d, 0);
	}
	return 0;
}