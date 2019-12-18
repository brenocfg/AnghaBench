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
struct dvb_frontend {struct cx24120_state* demodulator_priv; } ;
struct cx24120_state {int /*<<< orphan*/  dnxt; int /*<<< orphan*/  dcur; } ;

/* Variables and functions */

__attribute__((used)) static void cx24120_clone_params(struct dvb_frontend *fe)
{
	struct cx24120_state *state = fe->demodulator_priv;

	state->dcur = state->dnxt;
}