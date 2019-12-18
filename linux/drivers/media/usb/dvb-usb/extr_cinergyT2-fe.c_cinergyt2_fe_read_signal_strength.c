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
typedef  scalar_t__ u16 ;
struct dvb_frontend {struct cinergyt2_fe_state* demodulator_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  gain; } ;
struct cinergyt2_fe_state {TYPE_1__ status; } ;

/* Variables and functions */
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cinergyt2_fe_read_signal_strength(struct dvb_frontend *fe,
						u16 *strength)
{
	struct cinergyt2_fe_state *state = fe->demodulator_priv;

	*strength = (0xffff - le16_to_cpu(state->status.gain));
	return 0;
}