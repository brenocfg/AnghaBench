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
struct serio {int /*<<< orphan*/  dev; int /*<<< orphan*/  node; int /*<<< orphan*/ * parent; int /*<<< orphan*/  child_node; int /*<<< orphan*/  (* stop ) (struct serio*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 scalar_t__ device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_continue_rx (int /*<<< orphan*/ *) ; 
 struct serio* serio_get_pending_child (struct serio*) ; 
 int /*<<< orphan*/  serio_pause_rx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_remove_pending_events (struct serio*) ; 
 int /*<<< orphan*/  stub1 (struct serio*) ; 

__attribute__((used)) static void serio_destroy_port(struct serio *serio)
{
	struct serio *child;

	while ((child = serio_get_pending_child(serio)) != NULL) {
		serio_remove_pending_events(child);
		put_device(&child->dev);
	}

	if (serio->stop)
		serio->stop(serio);

	if (serio->parent) {
		serio_pause_rx(serio->parent);
		list_del_init(&serio->child_node);
		serio_continue_rx(serio->parent);
		serio->parent = NULL;
	}

	if (device_is_registered(&serio->dev))
		device_del(&serio->dev);

	list_del_init(&serio->node);
	serio_remove_pending_events(serio);
	put_device(&serio->dev);
}