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
struct fsl_mc_device {int dummy; } ;
struct fsl_mc_child_objs {int child_count; struct fsl_mc_obj_desc* child_array; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ fsl_mc_device_match (struct fsl_mc_device*,struct fsl_mc_obj_desc*) ; 
 int /*<<< orphan*/  fsl_mc_device_remove (struct fsl_mc_device*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 struct fsl_mc_device* to_fsl_mc_device (struct device*) ; 

__attribute__((used)) static int __fsl_mc_device_remove_if_not_in_mc(struct device *dev, void *data)
{
	int i;
	struct fsl_mc_child_objs *objs;
	struct fsl_mc_device *mc_dev;

	mc_dev = to_fsl_mc_device(dev);
	objs = data;

	for (i = 0; i < objs->child_count; i++) {
		struct fsl_mc_obj_desc *obj_desc = &objs->child_array[i];

		if (strlen(obj_desc->type) != 0 &&
		    fsl_mc_device_match(mc_dev, obj_desc))
			break;
	}

	if (i == objs->child_count)
		fsl_mc_device_remove(mc_dev);

	return 0;
}