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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct ubi_device {int ubi_num; TYPE_1__ cdev; } ;

/* Variables and functions */
 int ENODEV ; 
 int MAJOR (int /*<<< orphan*/ ) ; 
 int UBI_MAX_DEVICES ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct ubi_device** ubi_devices ; 
 int /*<<< orphan*/  ubi_devices_lock ; 

int ubi_major2num(int major)
{
	int i, ubi_num = -ENODEV;

	spin_lock(&ubi_devices_lock);
	for (i = 0; i < UBI_MAX_DEVICES; i++) {
		struct ubi_device *ubi = ubi_devices[i];

		if (ubi && MAJOR(ubi->cdev.dev) == major) {
			ubi_num = ubi->ubi_num;
			break;
		}
	}
	spin_unlock(&ubi_devices_lock);

	return ubi_num;
}