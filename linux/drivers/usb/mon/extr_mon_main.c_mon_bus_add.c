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
struct usb_bus {int monitored; } ;
struct TYPE_2__ {scalar_t__ nreaders; } ;

/* Variables and functions */
 TYPE_1__ mon_bus0 ; 
 int /*<<< orphan*/  mon_bus_init (struct usb_bus*) ; 
 int /*<<< orphan*/  mon_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mon_bus_add(struct usb_bus *ubus)
{
	mon_bus_init(ubus);
	mutex_lock(&mon_lock);
	if (mon_bus0.nreaders != 0)
		ubus->monitored = 1;
	mutex_unlock(&mon_lock);
}