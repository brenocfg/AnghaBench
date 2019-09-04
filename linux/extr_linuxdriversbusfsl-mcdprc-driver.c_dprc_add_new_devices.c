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
struct fsl_mc_obj_desc {int /*<<< orphan*/  type; } ;
struct fsl_mc_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_plugged_state_change (struct fsl_mc_device*,struct fsl_mc_obj_desc*) ; 
 int fsl_mc_device_add (struct fsl_mc_obj_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct fsl_mc_device**) ; 
 struct fsl_mc_device* fsl_mc_device_lookup (struct fsl_mc_obj_desc*,struct fsl_mc_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dprc_add_new_devices(struct fsl_mc_device *mc_bus_dev,
				 struct fsl_mc_obj_desc *obj_desc_array,
				 int num_child_objects_in_mc)
{
	int error;
	int i;

	for (i = 0; i < num_child_objects_in_mc; i++) {
		struct fsl_mc_device *child_dev;
		struct fsl_mc_obj_desc *obj_desc = &obj_desc_array[i];

		if (strlen(obj_desc->type) == 0)
			continue;

		/*
		 * Check if device is already known to Linux:
		 */
		child_dev = fsl_mc_device_lookup(obj_desc, mc_bus_dev);
		if (child_dev) {
			check_plugged_state_change(child_dev, obj_desc);
			put_device(&child_dev->dev);
			continue;
		}

		error = fsl_mc_device_add(obj_desc, NULL, &mc_bus_dev->dev,
					  &child_dev);
		if (error < 0)
			continue;
	}
}