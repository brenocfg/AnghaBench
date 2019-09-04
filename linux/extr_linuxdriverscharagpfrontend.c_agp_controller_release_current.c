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
struct TYPE_2__ {int used_by_controller; int /*<<< orphan*/ * current_controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_FF_IS_VALID ; 
 int /*<<< orphan*/  agp_backend_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_bridge ; 
 TYPE_1__ agp_fe ; 
 struct agp_file_private* agp_find_private (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void agp_controller_release_current(struct agp_controller *controller,
				      struct agp_file_private *controller_priv)
{
	struct agp_client *clients;

	clear_bit(AGP_FF_IS_VALID, &controller_priv->access_flags);
	clients = controller->clients;

	while (clients != NULL) {
		struct agp_file_private *priv;

		priv = agp_find_private(clients->pid);

		if (priv != NULL)
			clear_bit(AGP_FF_IS_VALID, &priv->access_flags);

		clients = clients->next;
	}

	agp_fe.current_controller = NULL;
	agp_fe.used_by_controller = false;
	agp_backend_release(agp_bridge);
}