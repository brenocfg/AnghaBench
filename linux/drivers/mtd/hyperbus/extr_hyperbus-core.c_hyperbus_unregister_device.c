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
struct hyperbus_device {scalar_t__ mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  map_destroy (scalar_t__) ; 
 int mtd_device_unregister (scalar_t__) ; 

int hyperbus_unregister_device(struct hyperbus_device *hbdev)
{
	int ret = 0;

	if (hbdev && hbdev->mtd) {
		ret = mtd_device_unregister(hbdev->mtd);
		map_destroy(hbdev->mtd);
	}

	return ret;
}