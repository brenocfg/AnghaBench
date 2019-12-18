#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct virtio_driver {unsigned int feature_table_size; unsigned int* feature_table; unsigned int* feature_table_legacy; unsigned int feature_table_size_legacy; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct virtio_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 struct virtio_driver* drv_to_virtio (int /*<<< orphan*/ ) ; 

void virtio_check_driver_offered_feature(const struct virtio_device *vdev,
					 unsigned int fbit)
{
	unsigned int i;
	struct virtio_driver *drv = drv_to_virtio(vdev->dev.driver);

	for (i = 0; i < drv->feature_table_size; i++)
		if (drv->feature_table[i] == fbit)
			return;

	if (drv->feature_table_legacy) {
		for (i = 0; i < drv->feature_table_size_legacy; i++)
			if (drv->feature_table_legacy[i] == fbit)
				return;
	}

	BUG();
}