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
struct serio {int /*<<< orphan*/  name; int /*<<< orphan*/  phys; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* start ) (struct serio*) ;int /*<<< orphan*/  node; int /*<<< orphan*/  children; int /*<<< orphan*/  child_node; struct serio* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_continue_rx (struct serio*) ; 
 int /*<<< orphan*/  serio_list ; 
 int /*<<< orphan*/  serio_pause_rx (struct serio*) ; 
 int /*<<< orphan*/  stub1 (struct serio*) ; 

__attribute__((used)) static void serio_add_port(struct serio *serio)
{
	struct serio *parent = serio->parent;
	int error;

	if (parent) {
		serio_pause_rx(parent);
		list_add_tail(&serio->child_node, &parent->children);
		serio_continue_rx(parent);
	}

	list_add_tail(&serio->node, &serio_list);

	if (serio->start)
		serio->start(serio);

	error = device_add(&serio->dev);
	if (error)
		dev_err(&serio->dev,
			"device_add() failed for %s (%s), error: %d\n",
			serio->phys, serio->name, error);
}