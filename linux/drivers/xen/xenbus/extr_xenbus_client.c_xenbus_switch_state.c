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
struct xenbus_device {int dummy; } ;
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;

/* Variables and functions */
 int __xenbus_switch_state (struct xenbus_device*,int,int /*<<< orphan*/ ) ; 

int xenbus_switch_state(struct xenbus_device *dev, enum xenbus_state state)
{
	return __xenbus_switch_state(dev, state, 0);
}