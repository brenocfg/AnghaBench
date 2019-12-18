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
struct ubi_vtbl_record {scalar_t__ upd_marker; } ;
struct ubi_volume {size_t vol_id; scalar_t__ vol_type; long long used_bytes; int used_ebs; scalar_t__ upd_marker; scalar_t__ usable_leb_size; scalar_t__ last_eb_bytes; scalar_t__ corrupted; } ;
struct ubi_device {int /*<<< orphan*/  device_mutex; struct ubi_vtbl_record* vtbl; } ;

/* Variables and functions */
 scalar_t__ UBI_STATIC_VOLUME ; 
 int /*<<< orphan*/  dbg_gen (char*,size_t) ; 
 int div_u64_rem (long long,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int ubi_change_vtbl_record (struct ubi_device*,size_t,struct ubi_vtbl_record*) ; 

__attribute__((used)) static int clear_update_marker(struct ubi_device *ubi, struct ubi_volume *vol,
			       long long bytes)
{
	int err;
	struct ubi_vtbl_record vtbl_rec;

	dbg_gen("clear update marker for volume %d", vol->vol_id);

	vtbl_rec = ubi->vtbl[vol->vol_id];
	ubi_assert(vol->upd_marker && vtbl_rec.upd_marker);
	vtbl_rec.upd_marker = 0;

	if (vol->vol_type == UBI_STATIC_VOLUME) {
		vol->corrupted = 0;
		vol->used_bytes = bytes;
		vol->used_ebs = div_u64_rem(bytes, vol->usable_leb_size,
					    &vol->last_eb_bytes);
		if (vol->last_eb_bytes)
			vol->used_ebs += 1;
		else
			vol->last_eb_bytes = vol->usable_leb_size;
	}

	mutex_lock(&ubi->device_mutex);
	err = ubi_change_vtbl_record(ubi, vol->vol_id, &vtbl_rec);
	vol->upd_marker = 0;
	mutex_unlock(&ubi->device_mutex);
	return err;
}