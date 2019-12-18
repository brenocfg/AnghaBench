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
struct TYPE_4__ {TYPE_1__* serio; } ;
struct psmouse {int /*<<< orphan*/ * private; TYPE_2__ ps2dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trackpoint_attr_group ; 

__attribute__((used)) static void trackpoint_disconnect(struct psmouse *psmouse)
{
	device_remove_group(&psmouse->ps2dev.serio->dev,
			    &trackpoint_attr_group);

	kfree(psmouse->private);
	psmouse->private = NULL;
}