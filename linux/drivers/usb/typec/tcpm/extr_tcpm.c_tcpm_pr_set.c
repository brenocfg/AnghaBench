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
struct typec_capability {int dummy; } ;
struct tcpm_port {scalar_t__ port_type; scalar_t__ state; int pwr_role; int swap_status; int swap_pending; int /*<<< orphan*/  swap_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  swap_complete; } ;
typedef  enum typec_role { ____Placeholder_typec_role } typec_role ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PD_ROLE_SWAP_TIMEOUT ; 
 int /*<<< orphan*/  PR_SWAP_SEND ; 
 scalar_t__ SNK_READY ; 
 scalar_t__ SRC_READY ; 
 scalar_t__ TYPEC_PORT_DRP ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpm_set_state (struct tcpm_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcpm_port* typec_cap_to_tcpm (struct typec_capability const*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcpm_pr_set(const struct typec_capability *cap,
		       enum typec_role role)
{
	struct tcpm_port *port = typec_cap_to_tcpm(cap);
	int ret;

	mutex_lock(&port->swap_lock);
	mutex_lock(&port->lock);

	if (port->port_type != TYPEC_PORT_DRP) {
		ret = -EINVAL;
		goto port_unlock;
	}
	if (port->state != SRC_READY && port->state != SNK_READY) {
		ret = -EAGAIN;
		goto port_unlock;
	}

	if (role == port->pwr_role) {
		ret = 0;
		goto port_unlock;
	}

	port->swap_status = 0;
	port->swap_pending = true;
	reinit_completion(&port->swap_complete);
	tcpm_set_state(port, PR_SWAP_SEND, 0);
	mutex_unlock(&port->lock);

	if (!wait_for_completion_timeout(&port->swap_complete,
				msecs_to_jiffies(PD_ROLE_SWAP_TIMEOUT)))
		ret = -ETIMEDOUT;
	else
		ret = port->swap_status;

	goto swap_unlock;

port_unlock:
	mutex_unlock(&port->lock);
swap_unlock:
	mutex_unlock(&port->swap_lock);
	return ret;
}