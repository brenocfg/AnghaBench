#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct agp_client {struct agp_client* prev; struct agp_client* next; } ;
struct TYPE_4__ {TYPE_1__* current_controller; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_clients; struct agp_client* clients; } ;

/* Variables and functions */
 TYPE_2__ agp_fe ; 

__attribute__((used)) static void agp_insert_client(struct agp_client *client)
{
	struct agp_client *prev_client;

	prev_client = agp_fe.current_controller->clients;
	client->next = prev_client;

	if (prev_client != NULL)
		prev_client->prev = client;

	agp_fe.current_controller->clients = client;
	agp_fe.current_controller->num_clients++;
}