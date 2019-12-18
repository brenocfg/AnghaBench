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
struct tcpm_port {int queued_message; int /*<<< orphan*/  state_machine; int /*<<< orphan*/  wq; } ;
typedef  enum pd_msg_request { ____Placeholder_pd_msg_request } pd_msg_request ;

/* Variables and functions */
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcpm_queue_message(struct tcpm_port *port,
			       enum pd_msg_request message)
{
	port->queued_message = message;
	mod_delayed_work(port->wq, &port->state_machine, 0);
}