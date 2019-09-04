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
struct ubi_volume_desc {scalar_t__ mode; struct ubi_volume* vol; } ;
struct ubi_volume {scalar_t__ vol_type; scalar_t__ upd_marker; int /*<<< orphan*/  vol_id; struct ubi_device* ubi; } ;
struct ubi_device {int dummy; } ;

/* Variables and functions */
 int EBADF ; 
 int EBADMSG ; 
 int EINVAL ; 
 int EROFS ; 
 scalar_t__ UBI_READONLY ; 
 scalar_t__ UBI_STATIC_VOLUME ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ubi_eba_is_mapped (struct ubi_volume*,int) ; 
 int ubi_eba_write_leb (struct ubi_device*,struct ubi_volume*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_leb_valid (struct ubi_volume*,int) ; 

int ubi_leb_map(struct ubi_volume_desc *desc, int lnum)
{
	struct ubi_volume *vol = desc->vol;
	struct ubi_device *ubi = vol->ubi;

	dbg_gen("map LEB %d:%d", vol->vol_id, lnum);

	if (desc->mode == UBI_READONLY || vol->vol_type == UBI_STATIC_VOLUME)
		return -EROFS;

	if (!ubi_leb_valid(vol, lnum))
		return -EINVAL;

	if (vol->upd_marker)
		return -EBADF;

	if (ubi_eba_is_mapped(vol, lnum))
		return -EBADMSG;

	return ubi_eba_write_leb(ubi, vol, lnum, NULL, 0, 0);
}