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
struct ubi_vtbl_record {int /*<<< orphan*/  reserved_pebs; } ;
struct ubi_volume_desc {struct ubi_volume* vol; } ;
struct ubi_volume {int vol_id; int reserved_pebs; scalar_t__ vol_type; int used_ebs; int ref_count; long long last_eb_bytes; long long usable_leb_size; long long used_bytes; struct ubi_device* ubi; } ;
struct ubi_eba_table {int dummy; } ;
struct ubi_device {int avail_pebs; int corr_peb_count; int rsvd_pebs; int /*<<< orphan*/  volumes_lock; struct ubi_vtbl_record* vtbl; int /*<<< orphan*/  ubi_num; scalar_t__ ro_mode; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOSPC ; 
 int EROFS ; 
 scalar_t__ IS_ERR (struct ubi_eba_table*) ; 
 int PTR_ERR (struct ubi_eba_table*) ; 
 int /*<<< orphan*/  UBI_ALL ; 
 scalar_t__ UBI_DYNAMIC_VOLUME ; 
 scalar_t__ UBI_STATIC_VOLUME ; 
 int /*<<< orphan*/  UBI_VOLUME_RESIZED ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  kfree (struct ubi_eba_table*) ; 
 int /*<<< orphan*/  self_check_volumes (struct ubi_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int ubi_change_vtbl_record (struct ubi_device*,int,struct ubi_vtbl_record*) ; 
 int /*<<< orphan*/  ubi_eba_copy_table (struct ubi_volume*,struct ubi_eba_table*,int) ; 
 struct ubi_eba_table* ubi_eba_create_table (struct ubi_volume*,int) ; 
 int /*<<< orphan*/  ubi_eba_replace_table (struct ubi_volume*,struct ubi_eba_table*) ; 
 int ubi_eba_unmap_leb (struct ubi_device*,struct ubi_volume*,int) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,int,...) ; 
 int /*<<< orphan*/  ubi_update_reserved (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_volume_notify (struct ubi_device*,struct ubi_volume*,int /*<<< orphan*/ ) ; 
 int ubi_wl_flush (struct ubi_device*,int,int /*<<< orphan*/ ) ; 

int ubi_resize_volume(struct ubi_volume_desc *desc, int reserved_pebs)
{
	int i, err, pebs;
	struct ubi_volume *vol = desc->vol;
	struct ubi_device *ubi = vol->ubi;
	struct ubi_vtbl_record vtbl_rec;
	struct ubi_eba_table *new_eba_tbl = NULL;
	int vol_id = vol->vol_id;

	if (ubi->ro_mode)
		return -EROFS;

	dbg_gen("re-size device %d, volume %d to from %d to %d PEBs",
		ubi->ubi_num, vol_id, vol->reserved_pebs, reserved_pebs);

	if (vol->vol_type == UBI_STATIC_VOLUME &&
	    reserved_pebs < vol->used_ebs) {
		ubi_err(ubi, "too small size %d, %d LEBs contain data",
			reserved_pebs, vol->used_ebs);
		return -EINVAL;
	}

	/* If the size is the same, we have nothing to do */
	if (reserved_pebs == vol->reserved_pebs)
		return 0;

	new_eba_tbl = ubi_eba_create_table(vol, reserved_pebs);
	if (IS_ERR(new_eba_tbl))
		return PTR_ERR(new_eba_tbl);

	spin_lock(&ubi->volumes_lock);
	if (vol->ref_count > 1) {
		spin_unlock(&ubi->volumes_lock);
		err = -EBUSY;
		goto out_free;
	}
	spin_unlock(&ubi->volumes_lock);

	/* Reserve physical eraseblocks */
	pebs = reserved_pebs - vol->reserved_pebs;
	if (pebs > 0) {
		spin_lock(&ubi->volumes_lock);
		if (pebs > ubi->avail_pebs) {
			ubi_err(ubi, "not enough PEBs: requested %d, available %d",
				pebs, ubi->avail_pebs);
			if (ubi->corr_peb_count)
				ubi_err(ubi, "%d PEBs are corrupted and not used",
					ubi->corr_peb_count);
			spin_unlock(&ubi->volumes_lock);
			err = -ENOSPC;
			goto out_free;
		}
		ubi->avail_pebs -= pebs;
		ubi->rsvd_pebs += pebs;
		ubi_eba_copy_table(vol, new_eba_tbl, vol->reserved_pebs);
		ubi_eba_replace_table(vol, new_eba_tbl);
		spin_unlock(&ubi->volumes_lock);
	}

	if (pebs < 0) {
		for (i = 0; i < -pebs; i++) {
			err = ubi_eba_unmap_leb(ubi, vol, reserved_pebs + i);
			if (err)
				goto out_acc;
		}
		spin_lock(&ubi->volumes_lock);
		ubi->rsvd_pebs += pebs;
		ubi->avail_pebs -= pebs;
		ubi_update_reserved(ubi);
		ubi_eba_copy_table(vol, new_eba_tbl, reserved_pebs);
		ubi_eba_replace_table(vol, new_eba_tbl);
		spin_unlock(&ubi->volumes_lock);
	}

	/*
	 * When we shrink a volume we have to flush all pending (erase) work.
	 * Otherwise it can happen that upon next attach UBI finds a LEB with
	 * lnum > highest_lnum and refuses to attach.
	 */
	if (pebs < 0) {
		err = ubi_wl_flush(ubi, vol_id, UBI_ALL);
		if (err)
			goto out_acc;
	}

	/* Change volume table record */
	vtbl_rec = ubi->vtbl[vol_id];
	vtbl_rec.reserved_pebs = cpu_to_be32(reserved_pebs);
	err = ubi_change_vtbl_record(ubi, vol_id, &vtbl_rec);
	if (err)
		goto out_acc;

	vol->reserved_pebs = reserved_pebs;
	if (vol->vol_type == UBI_DYNAMIC_VOLUME) {
		vol->used_ebs = reserved_pebs;
		vol->last_eb_bytes = vol->usable_leb_size;
		vol->used_bytes =
			(long long)vol->used_ebs * vol->usable_leb_size;
	}

	ubi_volume_notify(ubi, vol, UBI_VOLUME_RESIZED);
	self_check_volumes(ubi);
	return err;

out_acc:
	if (pebs > 0) {
		spin_lock(&ubi->volumes_lock);
		ubi->rsvd_pebs -= pebs;
		ubi->avail_pebs += pebs;
		spin_unlock(&ubi->volumes_lock);
	}
out_free:
	kfree(new_eba_tbl);
	return err;
}