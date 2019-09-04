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
struct ide_disk_obj {int /*<<< orphan*/  dev; int /*<<< orphan*/  drive; } ;
struct gendisk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 scalar_t__ ide_device_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_disk_obj ; 
 int /*<<< orphan*/  ide_disk_ref_mutex ; 
 struct ide_disk_obj* ide_drv_g (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ide_disk_obj *ide_disk_get(struct gendisk *disk)
{
	struct ide_disk_obj *idkp = NULL;

	mutex_lock(&ide_disk_ref_mutex);
	idkp = ide_drv_g(disk, ide_disk_obj);
	if (idkp) {
		if (ide_device_get(idkp->drive))
			idkp = NULL;
		else
			get_device(&idkp->dev);
	}
	mutex_unlock(&ide_disk_ref_mutex);
	return idkp;
}