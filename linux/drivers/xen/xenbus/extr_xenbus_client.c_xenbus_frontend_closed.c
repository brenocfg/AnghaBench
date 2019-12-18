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
struct xenbus_device {int /*<<< orphan*/  down; } ;

/* Variables and functions */
 int /*<<< orphan*/  XenbusStateClosed ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,int /*<<< orphan*/ ) ; 

int xenbus_frontend_closed(struct xenbus_device *dev)
{
	xenbus_switch_state(dev, XenbusStateClosed);
	complete(&dev->down);
	return 0;
}