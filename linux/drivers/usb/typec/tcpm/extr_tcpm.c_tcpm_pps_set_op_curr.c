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
typedef  int u16 ;
struct TYPE_2__ {int max_curr; int out_volt; int op_curr; int /*<<< orphan*/  active; } ;
struct tcpm_port {scalar_t__ state; unsigned int operating_snk_mw; int pps_status; int pps_pending; int /*<<< orphan*/  swap_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  pps_complete; TYPE_1__ pps_data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PD_PPS_CTRL_TIMEOUT ; 
 int RDO_PROG_CURR_MA_STEP ; 
 int /*<<< orphan*/  SNK_NEGOTIATE_PPS_CAPABILITIES ; 
 scalar_t__ SNK_READY ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpm_set_state (struct tcpm_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcpm_pps_set_op_curr(struct tcpm_port *port, u16 op_curr)
{
	unsigned int target_mw;
	int ret;

	mutex_lock(&port->swap_lock);
	mutex_lock(&port->lock);

	if (!port->pps_data.active) {
		ret = -EOPNOTSUPP;
		goto port_unlock;
	}

	if (port->state != SNK_READY) {
		ret = -EAGAIN;
		goto port_unlock;
	}

	if (op_curr > port->pps_data.max_curr) {
		ret = -EINVAL;
		goto port_unlock;
	}

	target_mw = (op_curr * port->pps_data.out_volt) / 1000;
	if (target_mw < port->operating_snk_mw) {
		ret = -EINVAL;
		goto port_unlock;
	}

	/* Round down operating current to align with PPS valid steps */
	op_curr = op_curr - (op_curr % RDO_PROG_CURR_MA_STEP);

	reinit_completion(&port->pps_complete);
	port->pps_data.op_curr = op_curr;
	port->pps_status = 0;
	port->pps_pending = true;
	tcpm_set_state(port, SNK_NEGOTIATE_PPS_CAPABILITIES, 0);
	mutex_unlock(&port->lock);

	if (!wait_for_completion_timeout(&port->pps_complete,
				msecs_to_jiffies(PD_PPS_CTRL_TIMEOUT)))
		ret = -ETIMEDOUT;
	else
		ret = port->pps_status;

	goto swap_unlock;

port_unlock:
	mutex_unlock(&port->lock);
swap_unlock:
	mutex_unlock(&port->swap_lock);

	return ret;
}