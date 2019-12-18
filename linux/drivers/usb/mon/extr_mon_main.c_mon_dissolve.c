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
struct usb_bus {int /*<<< orphan*/ * mon_bus; scalar_t__ monitored; } ;
struct mon_bus {int /*<<< orphan*/ * u_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void mon_dissolve(struct mon_bus *mbus, struct usb_bus *ubus)
{

	if (ubus->monitored) {
		ubus->monitored = 0;
		mb();
	}

	ubus->mon_bus = NULL;
	mbus->u_bus = NULL;
	mb();

	/* We want synchronize_irq() here, but that needs an argument. */
}