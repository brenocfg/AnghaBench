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
struct fsl_mc_obj_desc {int dummy; } ;
struct fsl_mc_device {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fsl_mc_device_match ; 
 struct device* device_find_child (int /*<<< orphan*/ *,struct fsl_mc_obj_desc*,int /*<<< orphan*/ ) ; 
 struct fsl_mc_device* to_fsl_mc_device (struct device*) ; 

__attribute__((used)) static struct fsl_mc_device *fsl_mc_device_lookup(struct fsl_mc_obj_desc
								*obj_desc,
						  struct fsl_mc_device
								*mc_bus_dev)
{
	struct device *dev;

	dev = device_find_child(&mc_bus_dev->dev, obj_desc,
				__fsl_mc_device_match);

	return dev ? to_fsl_mc_device(dev) : NULL;
}