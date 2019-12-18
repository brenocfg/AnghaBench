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
struct mei_device {int dummy; } ;
struct mei_cl_device {int do_match; } ;

/* Variables and functions */
 int /*<<< orphan*/  mei_cl_bus_dev_fixup (struct mei_cl_device*) ; 
 int /*<<< orphan*/  mei_cl_bus_set_name (struct mei_cl_device*) ; 

__attribute__((used)) static bool mei_cl_bus_dev_setup(struct mei_device *bus,
				 struct mei_cl_device *cldev)
{
	cldev->do_match = 1;
	mei_cl_bus_dev_fixup(cldev);

	/* the device name can change during fix up */
	if (cldev->do_match)
		mei_cl_bus_set_name(cldev);

	return cldev->do_match == 1;
}