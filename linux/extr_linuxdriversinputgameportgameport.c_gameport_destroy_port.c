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
struct gameport {int /*<<< orphan*/  dev; int /*<<< orphan*/  node; TYPE_1__* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/ * child; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 scalar_t__ device_is_registered (int /*<<< orphan*/ *) ; 
 struct gameport* gameport_get_pending_child (struct gameport*) ; 
 int /*<<< orphan*/  gameport_remove_pending_events (struct gameport*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gameport_destroy_port(struct gameport *gameport)
{
	struct gameport *child;

	child = gameport_get_pending_child(gameport);
	if (child) {
		gameport_remove_pending_events(child);
		put_device(&child->dev);
	}

	if (gameport->parent) {
		gameport->parent->child = NULL;
		gameport->parent = NULL;
	}

	if (device_is_registered(&gameport->dev))
		device_del(&gameport->dev);

	list_del_init(&gameport->node);

	gameport_remove_pending_events(gameport);
	put_device(&gameport->dev);
}