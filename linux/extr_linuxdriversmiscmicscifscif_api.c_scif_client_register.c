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
struct subsys_interface {int /*<<< orphan*/  remove_dev; int /*<<< orphan*/  add_dev; int /*<<< orphan*/ * subsys; int /*<<< orphan*/  name; } ;
struct scif_client {struct subsys_interface si; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  scif_add_client_dev ; 
 int /*<<< orphan*/  scif_peer_bus ; 
 int /*<<< orphan*/  scif_remove_client_dev ; 
 int subsys_interface_register (struct subsys_interface*) ; 

int scif_client_register(struct scif_client *client)
{
	struct subsys_interface *si = &client->si;

	si->name = client->name;
	si->subsys = &scif_peer_bus;
	si->add_dev = scif_add_client_dev;
	si->remove_dev = scif_remove_client_dev;

	return subsys_interface_register(&client->si);
}