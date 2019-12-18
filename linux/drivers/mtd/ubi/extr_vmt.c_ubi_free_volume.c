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
struct ubi_volume {size_t vol_id; int /*<<< orphan*/  dev; int /*<<< orphan*/  cdev; } ;
struct ubi_device {int /*<<< orphan*/ ** volumes; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg_gen (char*,size_t) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 

void ubi_free_volume(struct ubi_device *ubi, struct ubi_volume *vol)
{
	dbg_gen("free volume %d", vol->vol_id);

	ubi->volumes[vol->vol_id] = NULL;
	cdev_del(&vol->cdev);
	device_unregister(&vol->dev);
}