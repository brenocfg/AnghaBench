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
struct hsi_port {int /*<<< orphan*/  n_head; } ;
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct hsi_client {void (* ehandler ) (struct hsi_client*,unsigned long) ;TYPE_1__ nb; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  hsi_event_notifier_call ; 
 struct hsi_port* hsi_get_port (struct hsi_client*) ; 
 int /*<<< orphan*/  hsi_port_claimed (struct hsi_client*) ; 

int hsi_register_port_event(struct hsi_client *cl,
			void (*handler)(struct hsi_client *, unsigned long))
{
	struct hsi_port *port = hsi_get_port(cl);

	if (!handler || cl->ehandler)
		return -EINVAL;
	if (!hsi_port_claimed(cl))
		return -EACCES;
	cl->ehandler = handler;
	cl->nb.notifier_call = hsi_event_notifier_call;

	return blocking_notifier_chain_register(&port->n_head, &cl->nb);
}