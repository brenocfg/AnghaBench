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
struct fmc_driver {int busid_n; scalar_t__* busid_val; } ;
struct fmc_device {scalar_t__ device_id; } ;

/* Variables and functions */
 int ENOENT ; 

__attribute__((used)) static int ff_validate(struct fmc_device *fmc, struct fmc_driver *drv)
{
	int i;

	if (!drv->busid_n)
		return 0; /* everyhing is valid */
	for (i = 0; i < drv->busid_n; i++)
		if (drv->busid_val[i] == fmc->device_id)
			return i;
	return -ENOENT;
}