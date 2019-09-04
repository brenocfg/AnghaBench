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
struct ubi_volume_desc {int mode; struct ubi_volume* vol; } ;
struct ubi_volume {int readers; int writers; int ref_count; int /*<<< orphan*/  dev; int /*<<< orphan*/  metaonly; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  vol_id; struct ubi_device* ubi; } ;
struct ubi_device {int /*<<< orphan*/  volumes_lock; int /*<<< orphan*/  ubi_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
#define  UBI_EXCLUSIVE 131 
#define  UBI_METAONLY 130 
#define  UBI_READONLY 129 
#define  UBI_READWRITE 128 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct ubi_volume_desc*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_put_device (struct ubi_device*) ; 

void ubi_close_volume(struct ubi_volume_desc *desc)
{
	struct ubi_volume *vol = desc->vol;
	struct ubi_device *ubi = vol->ubi;

	dbg_gen("close device %d, volume %d, mode %d",
		ubi->ubi_num, vol->vol_id, desc->mode);

	spin_lock(&ubi->volumes_lock);
	switch (desc->mode) {
	case UBI_READONLY:
		vol->readers -= 1;
		break;
	case UBI_READWRITE:
		vol->writers -= 1;
		break;
	case UBI_EXCLUSIVE:
		vol->exclusive = 0;
		break;
	case UBI_METAONLY:
		vol->metaonly = 0;
		break;
	}
	vol->ref_count -= 1;
	spin_unlock(&ubi->volumes_lock);

	kfree(desc);
	put_device(&vol->dev);
	ubi_put_device(ubi);
	module_put(THIS_MODULE);
}