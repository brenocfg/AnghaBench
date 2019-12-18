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
struct ubi_vtbl_record {int /*<<< orphan*/  flags; } ;
struct ubi_volume_desc {struct ubi_volume* vol; } ;
struct ubi_volume {int reserved_pebs; int /*<<< orphan*/  name; } ;
struct ubi_device {scalar_t__ avail_pebs; struct ubi_vtbl_record* vtbl; scalar_t__ ro_mode; struct ubi_volume** volumes; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBI_VTBL_AUTORESIZE_FLG ; 
 int ubi_change_vtbl_record (struct ubi_device*,int,struct ubi_vtbl_record*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,int) ; 
 int /*<<< orphan*/  ubi_msg (struct ubi_device*,char*,int,int /*<<< orphan*/ ,int,int) ; 
 int ubi_resize_volume (struct ubi_volume_desc*,scalar_t__) ; 
 int /*<<< orphan*/  ubi_warn (struct ubi_device*,char*) ; 

__attribute__((used)) static int autoresize(struct ubi_device *ubi, int vol_id)
{
	struct ubi_volume_desc desc;
	struct ubi_volume *vol = ubi->volumes[vol_id];
	int err, old_reserved_pebs = vol->reserved_pebs;

	if (ubi->ro_mode) {
		ubi_warn(ubi, "skip auto-resize because of R/O mode");
		return 0;
	}

	/*
	 * Clear the auto-resize flag in the volume in-memory copy of the
	 * volume table, and 'ubi_resize_volume()' will propagate this change
	 * to the flash.
	 */
	ubi->vtbl[vol_id].flags &= ~UBI_VTBL_AUTORESIZE_FLG;

	if (ubi->avail_pebs == 0) {
		struct ubi_vtbl_record vtbl_rec;

		/*
		 * No available PEBs to re-size the volume, clear the flag on
		 * flash and exit.
		 */
		vtbl_rec = ubi->vtbl[vol_id];
		err = ubi_change_vtbl_record(ubi, vol_id, &vtbl_rec);
		if (err)
			ubi_err(ubi, "cannot clean auto-resize flag for volume %d",
				vol_id);
	} else {
		desc.vol = vol;
		err = ubi_resize_volume(&desc,
					old_reserved_pebs + ubi->avail_pebs);
		if (err)
			ubi_err(ubi, "cannot auto-resize volume %d",
				vol_id);
	}

	if (err)
		return err;

	ubi_msg(ubi, "volume %d (\"%s\") re-sized from %d to %d LEBs",
		vol_id, vol->name, old_reserved_pebs, vol->reserved_pebs);
	return 0;
}