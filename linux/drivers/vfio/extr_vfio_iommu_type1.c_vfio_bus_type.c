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
struct device {struct bus_type* bus; } ;
struct bus_type {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int vfio_bus_type(struct device *dev, void *data)
{
	struct bus_type **bus = data;

	if (*bus && *bus != dev->bus)
		return -EINVAL;

	*bus = dev->bus;

	return 0;
}