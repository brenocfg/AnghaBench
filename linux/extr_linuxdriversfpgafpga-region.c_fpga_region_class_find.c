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
struct fpga_region {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* class_find_device (int /*<<< orphan*/ ,struct device*,void const*,int (*) (struct device*,void const*)) ; 
 int /*<<< orphan*/  fpga_region_class ; 
 struct fpga_region* to_fpga_region (struct device*) ; 

struct fpga_region *fpga_region_class_find(
	struct device *start, const void *data,
	int (*match)(struct device *, const void *))
{
	struct device *dev;

	dev = class_find_device(fpga_region_class, start, data, match);
	if (!dev)
		return NULL;

	return to_fpga_region(dev);
}