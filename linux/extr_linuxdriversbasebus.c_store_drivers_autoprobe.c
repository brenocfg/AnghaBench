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
struct bus_type {TYPE_1__* p; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int drivers_autoprobe; } ;

/* Variables and functions */

__attribute__((used)) static ssize_t store_drivers_autoprobe(struct bus_type *bus,
				       const char *buf, size_t count)
{
	if (buf[0] == '0')
		bus->p->drivers_autoprobe = 0;
	else
		bus->p->drivers_autoprobe = 1;
	return count;
}