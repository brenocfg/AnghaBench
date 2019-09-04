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
struct agp_controller {struct agp_controller* prev; struct agp_controller* next; } ;
struct TYPE_2__ {int backend_acquired; struct agp_controller* current_controller; struct agp_controller* controllers; } ;

/* Variables and functions */
 int /*<<< orphan*/  agp_backend_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_bridge ; 
 TYPE_1__ agp_fe ; 
 int /*<<< orphan*/  agp_remove_all_clients (struct agp_controller*) ; 
 int /*<<< orphan*/  agp_remove_all_memory (struct agp_controller*) ; 
 int /*<<< orphan*/  kfree (struct agp_controller*) ; 

__attribute__((used)) static int agp_remove_controller(struct agp_controller *controller)
{
	struct agp_controller *prev_controller;
	struct agp_controller *next_controller;

	prev_controller = controller->prev;
	next_controller = controller->next;

	if (prev_controller != NULL) {
		prev_controller->next = next_controller;
		if (next_controller != NULL)
			next_controller->prev = prev_controller;

	} else {
		if (next_controller != NULL)
			next_controller->prev = NULL;

		agp_fe.controllers = next_controller;
	}

	agp_remove_all_memory(controller);
	agp_remove_all_clients(controller);

	if (agp_fe.current_controller == controller) {
		agp_fe.current_controller = NULL;
		agp_fe.backend_acquired = false;
		agp_backend_release(agp_bridge);
	}
	kfree(controller);
	return 0;
}