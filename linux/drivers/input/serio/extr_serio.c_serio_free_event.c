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
struct serio_event {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct serio_event*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serio_free_event(struct serio_event *event)
{
	module_put(event->owner);
	kfree(event);
}