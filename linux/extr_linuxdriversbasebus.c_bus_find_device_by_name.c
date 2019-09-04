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
struct device {int dummy; } ;
struct bus_type {int dummy; } ;

/* Variables and functions */
 struct device* bus_find_device (struct bus_type*,struct device*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_name ; 

struct device *bus_find_device_by_name(struct bus_type *bus,
				       struct device *start, const char *name)
{
	return bus_find_device(bus, start, (void *)name, match_name);
}