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
struct hsi_port {int /*<<< orphan*/  n_head; } ;
struct hsi_client {int /*<<< orphan*/ * ehandler; int /*<<< orphan*/  nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int blocking_notifier_chain_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct hsi_port* hsi_get_port (struct hsi_client*) ; 
 int /*<<< orphan*/  hsi_port_claimed (struct hsi_client*) ; 

int hsi_unregister_port_event(struct hsi_client *cl)
{
	struct hsi_port *port = hsi_get_port(cl);
	int err;

	WARN_ON(!hsi_port_claimed(cl));

	err = blocking_notifier_chain_unregister(&port->n_head, &cl->nb);
	if (!err)
		cl->ehandler = NULL;

	return err;
}