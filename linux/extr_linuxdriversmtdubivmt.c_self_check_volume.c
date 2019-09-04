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
struct ubi_volume {scalar_t__ reserved_pebs; long long alignment; long long data_pad; int name_len; int vol_type; int upd_marker; long long usable_leb_size; scalar_t__ used_ebs; long long last_eb_bytes; long long used_bytes; int /*<<< orphan*/  name; scalar_t__ skip_check; scalar_t__ corrupted; } ;
struct ubi_device {long long leb_size; int min_io_size; scalar_t__ good_peb_count; int /*<<< orphan*/  volumes_lock; TYPE_1__* vtbl; struct ubi_volume** volumes; } ;
struct TYPE_2__ {int upd_marker; char* name; scalar_t__ vol_type; int /*<<< orphan*/  name_len; int /*<<< orphan*/  data_pad; int /*<<< orphan*/  alignment; int /*<<< orphan*/  reserved_pebs; } ;

/* Variables and functions */
 int EINVAL ; 
 int UBI_DYNAMIC_VOLUME ; 
 int UBI_STATIC_VOLUME ; 
 scalar_t__ UBI_VID_DYNAMIC ; 
 int UBI_VOL_NAME_MAX ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 long long strnlen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ubi_dump_vol_info (struct ubi_volume const*) ; 
 int /*<<< orphan*/  ubi_dump_vtbl_record (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,...) ; 
 int vol_id2idx (struct ubi_device*,int) ; 

__attribute__((used)) static int self_check_volume(struct ubi_device *ubi, int vol_id)
{
	int idx = vol_id2idx(ubi, vol_id);
	int reserved_pebs, alignment, data_pad, vol_type, name_len, upd_marker;
	const struct ubi_volume *vol;
	long long n;
	const char *name;

	spin_lock(&ubi->volumes_lock);
	reserved_pebs = be32_to_cpu(ubi->vtbl[vol_id].reserved_pebs);
	vol = ubi->volumes[idx];

	if (!vol) {
		if (reserved_pebs) {
			ubi_err(ubi, "no volume info, but volume exists");
			goto fail;
		}
		spin_unlock(&ubi->volumes_lock);
		return 0;
	}

	if (vol->reserved_pebs < 0 || vol->alignment < 0 || vol->data_pad < 0 ||
	    vol->name_len < 0) {
		ubi_err(ubi, "negative values");
		goto fail;
	}
	if (vol->alignment > ubi->leb_size || vol->alignment == 0) {
		ubi_err(ubi, "bad alignment");
		goto fail;
	}

	n = vol->alignment & (ubi->min_io_size - 1);
	if (vol->alignment != 1 && n) {
		ubi_err(ubi, "alignment is not multiple of min I/O unit");
		goto fail;
	}

	n = ubi->leb_size % vol->alignment;
	if (vol->data_pad != n) {
		ubi_err(ubi, "bad data_pad, has to be %lld", n);
		goto fail;
	}

	if (vol->vol_type != UBI_DYNAMIC_VOLUME &&
	    vol->vol_type != UBI_STATIC_VOLUME) {
		ubi_err(ubi, "bad vol_type");
		goto fail;
	}

	if (vol->upd_marker && vol->corrupted) {
		ubi_err(ubi, "update marker and corrupted simultaneously");
		goto fail;
	}

	if (vol->reserved_pebs > ubi->good_peb_count) {
		ubi_err(ubi, "too large reserved_pebs");
		goto fail;
	}

	n = ubi->leb_size - vol->data_pad;
	if (vol->usable_leb_size != ubi->leb_size - vol->data_pad) {
		ubi_err(ubi, "bad usable_leb_size, has to be %lld", n);
		goto fail;
	}

	if (vol->name_len > UBI_VOL_NAME_MAX) {
		ubi_err(ubi, "too long volume name, max is %d",
			UBI_VOL_NAME_MAX);
		goto fail;
	}

	n = strnlen(vol->name, vol->name_len + 1);
	if (n != vol->name_len) {
		ubi_err(ubi, "bad name_len %lld", n);
		goto fail;
	}

	n = (long long)vol->used_ebs * vol->usable_leb_size;
	if (vol->vol_type == UBI_DYNAMIC_VOLUME) {
		if (vol->corrupted) {
			ubi_err(ubi, "corrupted dynamic volume");
			goto fail;
		}
		if (vol->used_ebs != vol->reserved_pebs) {
			ubi_err(ubi, "bad used_ebs");
			goto fail;
		}
		if (vol->last_eb_bytes != vol->usable_leb_size) {
			ubi_err(ubi, "bad last_eb_bytes");
			goto fail;
		}
		if (vol->used_bytes != n) {
			ubi_err(ubi, "bad used_bytes");
			goto fail;
		}

		if (vol->skip_check) {
			ubi_err(ubi, "bad skip_check");
			goto fail;
		}
	} else {
		if (vol->used_ebs < 0 || vol->used_ebs > vol->reserved_pebs) {
			ubi_err(ubi, "bad used_ebs");
			goto fail;
		}
		if (vol->last_eb_bytes < 0 ||
		    vol->last_eb_bytes > vol->usable_leb_size) {
			ubi_err(ubi, "bad last_eb_bytes");
			goto fail;
		}
		if (vol->used_bytes < 0 || vol->used_bytes > n ||
		    vol->used_bytes < n - vol->usable_leb_size) {
			ubi_err(ubi, "bad used_bytes");
			goto fail;
		}
	}

	alignment  = be32_to_cpu(ubi->vtbl[vol_id].alignment);
	data_pad   = be32_to_cpu(ubi->vtbl[vol_id].data_pad);
	name_len   = be16_to_cpu(ubi->vtbl[vol_id].name_len);
	upd_marker = ubi->vtbl[vol_id].upd_marker;
	name       = &ubi->vtbl[vol_id].name[0];
	if (ubi->vtbl[vol_id].vol_type == UBI_VID_DYNAMIC)
		vol_type = UBI_DYNAMIC_VOLUME;
	else
		vol_type = UBI_STATIC_VOLUME;

	if (alignment != vol->alignment || data_pad != vol->data_pad ||
	    upd_marker != vol->upd_marker || vol_type != vol->vol_type ||
	    name_len != vol->name_len || strncmp(name, vol->name, name_len)) {
		ubi_err(ubi, "volume info is different");
		goto fail;
	}

	spin_unlock(&ubi->volumes_lock);
	return 0;

fail:
	ubi_err(ubi, "self-check failed for volume %d", vol_id);
	if (vol)
		ubi_dump_vol_info(vol);
	ubi_dump_vtbl_record(&ubi->vtbl[vol_id], vol_id);
	dump_stack();
	spin_unlock(&ubi->volumes_lock);
	return -EINVAL;
}