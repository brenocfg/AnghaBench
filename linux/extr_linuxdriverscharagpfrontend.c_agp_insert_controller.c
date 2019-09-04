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
struct TYPE_2__ {struct agp_controller* controllers; } ;

/* Variables and functions */
 TYPE_1__ agp_fe ; 

__attribute__((used)) static int agp_insert_controller(struct agp_controller *controller)
{
	struct agp_controller *prev_controller;

	prev_controller = agp_fe.controllers;
	controller->next = prev_controller;

	if (prev_controller != NULL)
		prev_controller->prev = controller;

	agp_fe.controllers = controller;

	return 0;
}