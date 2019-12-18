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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_frontend {struct af9013_state* demodulator_priv; } ;
struct af9013_state {int /*<<< orphan*/  dvbv3_strength; } ;

/* Variables and functions */

__attribute__((used)) static int af9013_read_signal_strength(struct dvb_frontend *fe, u16 *strength)
{
	struct af9013_state *state = fe->demodulator_priv;

	*strength = state->dvbv3_strength;

	return 0;
}