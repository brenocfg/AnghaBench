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
struct ubi_volume_desc {struct ubi_volume* vol; } ;
struct ubi_volume {int vol_id; int used_ebs; int usable_leb_size; scalar_t__ vol_type; int last_eb_bytes; scalar_t__ upd_marker; struct ubi_device* ubi; } ;
struct ubi_device {int vtbl_slots; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 scalar_t__ UBI_STATIC_VOLUME ; 

__attribute__((used)) static int leb_read_sanity_check(struct ubi_volume_desc *desc, int lnum,
				 int offset, int len)
{
	struct ubi_volume *vol = desc->vol;
	struct ubi_device *ubi = vol->ubi;
	int vol_id = vol->vol_id;

	if (vol_id < 0 || vol_id >= ubi->vtbl_slots || lnum < 0 ||
	    lnum >= vol->used_ebs || offset < 0 || len < 0 ||
	    offset + len > vol->usable_leb_size)
		return -EINVAL;

	if (vol->vol_type == UBI_STATIC_VOLUME) {
		if (vol->used_ebs == 0)
			/* Empty static UBI volume */
			return 0;
		if (lnum == vol->used_ebs - 1 &&
		    offset + len > vol->last_eb_bytes)
			return -EINVAL;
	}

	if (vol->upd_marker)
		return -EBADF;

	return 0;
}