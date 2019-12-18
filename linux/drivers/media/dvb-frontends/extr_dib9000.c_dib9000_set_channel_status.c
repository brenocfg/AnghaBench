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
struct dvb_frontend_parametersContext {int dummy; } ;
struct dvb_frontend {struct dib9000_state* demodulator_priv; } ;
struct dib9000_state {int /*<<< orphan*/  channel_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dvb_frontend_parametersContext*,int) ; 

__attribute__((used)) static int dib9000_set_channel_status(struct dvb_frontend *fe, struct dvb_frontend_parametersContext *channel_status)
{
	struct dib9000_state *state = fe->demodulator_priv;

	memcpy(&state->channel_status, channel_status, sizeof(struct dvb_frontend_parametersContext));
	return 0;
}