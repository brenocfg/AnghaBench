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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_frontend {struct as102_state* demodulator_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  mer; } ;
struct as102_state {TYPE_1__ demod_stats; } ;

/* Variables and functions */

__attribute__((used)) static int as102_fe_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct as102_state *state = fe->demodulator_priv;

	*snr = state->demod_stats.mer;

	return 0;
}