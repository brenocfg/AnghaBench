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
struct dvb_frontend {struct cx24117_state* demodulator_priv; } ;
struct cx24117_state {TYPE_1__* priv; } ;
struct cx24117_cmd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fe_lock; } ;

/* Variables and functions */
 int cx24117_cmd_execute_nolock (struct dvb_frontend*,struct cx24117_cmd*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cx24117_cmd_execute(struct dvb_frontend *fe, struct cx24117_cmd *cmd)
{
	struct cx24117_state *state = fe->demodulator_priv;
	int ret;

	mutex_lock(&state->priv->fe_lock);
	ret = cx24117_cmd_execute_nolock(fe, cmd);
	mutex_unlock(&state->priv->fe_lock);

	return ret;
}