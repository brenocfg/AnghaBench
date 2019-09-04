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
struct fsl_mc_device {int /*<<< orphan*/  dev; scalar_t__ resource; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fsl_mc_is_allocatable (struct fsl_mc_device*) ; 
 int fsl_mc_resource_pool_remove_device (struct fsl_mc_device*) ; 

__attribute__((used)) static int fsl_mc_allocator_remove(struct fsl_mc_device *mc_dev)
{
	int error;

	if (!fsl_mc_is_allocatable(mc_dev))
		return -EINVAL;

	if (mc_dev->resource) {
		error = fsl_mc_resource_pool_remove_device(mc_dev);
		if (error < 0)
			return error;
	}

	dev_dbg(&mc_dev->dev,
		"Allocatable fsl-mc device unbound from fsl_mc_allocator driver");
	return 0;
}