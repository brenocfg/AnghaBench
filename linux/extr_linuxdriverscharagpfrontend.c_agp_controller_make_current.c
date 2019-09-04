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
struct agp_file_private {int /*<<< orphan*/  access_flags; } ;
struct agp_controller {struct agp_client* clients; } ;
struct agp_client {struct agp_client* next; int /*<<< orphan*/  pid; } ;
struct TYPE_2__ {struct agp_controller* current_controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_FF_IS_CLIENT ; 
 int /*<<< orphan*/  AGP_FF_IS_VALID ; 
 TYPE_1__ agp_fe ; 
 struct agp_file_private* agp_find_private (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void agp_controller_make_current(struct agp_controller *controller)
{
	struct agp_client *clients;

	clients = controller->clients;

	while (clients != NULL) {
		struct agp_file_private *priv;

		priv = agp_find_private(clients->pid);

		if (priv != NULL) {
			set_bit(AGP_FF_IS_VALID, &priv->access_flags);
			set_bit(AGP_FF_IS_CLIENT, &priv->access_flags);
		}
		clients = clients->next;
	}

	agp_fe.current_controller = controller;
}