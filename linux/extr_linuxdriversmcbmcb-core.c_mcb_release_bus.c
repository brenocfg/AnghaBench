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
struct mcb_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mcb_devices_unregister (struct mcb_bus*) ; 

void mcb_release_bus(struct mcb_bus *bus)
{
	mcb_devices_unregister(bus);
}