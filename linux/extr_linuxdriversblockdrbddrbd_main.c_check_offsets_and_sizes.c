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
struct drbd_md {int al_offset; int bm_offset; int al_size_4k; int md_size_sect; scalar_t__ meta_dev_idx; int al_stripes; int al_stripe_size_4k; int la_size_sect; } ;
struct drbd_device {int dummy; } ;
struct drbd_backing_dev {struct drbd_md md; int /*<<< orphan*/  md_bdev; } ;
typedef  scalar_t__ sector_t ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MD_128MB_SECT ; 
 int MD_32kB_SECT ; 
 int MD_4kB_SECT ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*,scalar_t__,int,int,int,int,scalar_t__,unsigned long long,unsigned long long) ; 
 scalar_t__ drbd_get_capacity (int /*<<< orphan*/ ) ; 
 scalar_t__ drbd_md_first_sector (struct drbd_backing_dev*) ; 

__attribute__((used)) static int check_offsets_and_sizes(struct drbd_device *device, struct drbd_backing_dev *bdev)
{
	sector_t capacity = drbd_get_capacity(bdev->md_bdev);
	struct drbd_md *in_core = &bdev->md;
	s32 on_disk_al_sect;
	s32 on_disk_bm_sect;

	/* The on-disk size of the activity log, calculated from offsets, and
	 * the size of the activity log calculated from the stripe settings,
	 * should match.
	 * Though we could relax this a bit: it is ok, if the striped activity log
	 * fits in the available on-disk activity log size.
	 * Right now, that would break how resize is implemented.
	 * TODO: make drbd_determine_dev_size() (and the drbdmeta tool) aware
	 * of possible unused padding space in the on disk layout. */
	if (in_core->al_offset < 0) {
		if (in_core->bm_offset > in_core->al_offset)
			goto err;
		on_disk_al_sect = -in_core->al_offset;
		on_disk_bm_sect = in_core->al_offset - in_core->bm_offset;
	} else {
		if (in_core->al_offset != MD_4kB_SECT)
			goto err;
		if (in_core->bm_offset < in_core->al_offset + in_core->al_size_4k * MD_4kB_SECT)
			goto err;

		on_disk_al_sect = in_core->bm_offset - MD_4kB_SECT;
		on_disk_bm_sect = in_core->md_size_sect - in_core->bm_offset;
	}

	/* old fixed size meta data is exactly that: fixed. */
	if (in_core->meta_dev_idx >= 0) {
		if (in_core->md_size_sect != MD_128MB_SECT
		||  in_core->al_offset != MD_4kB_SECT
		||  in_core->bm_offset != MD_4kB_SECT + MD_32kB_SECT
		||  in_core->al_stripes != 1
		||  in_core->al_stripe_size_4k != MD_32kB_SECT/8)
			goto err;
	}

	if (capacity < in_core->md_size_sect)
		goto err;
	if (capacity - in_core->md_size_sect < drbd_md_first_sector(bdev))
		goto err;

	/* should be aligned, and at least 32k */
	if ((on_disk_al_sect & 7) || (on_disk_al_sect < MD_32kB_SECT))
		goto err;

	/* should fit (for now: exactly) into the available on-disk space;
	 * overflow prevention is in check_activity_log_stripe_size() above. */
	if (on_disk_al_sect != in_core->al_size_4k * MD_4kB_SECT)
		goto err;

	/* again, should be aligned */
	if (in_core->bm_offset & 7)
		goto err;

	/* FIXME check for device grow with flex external meta data? */

	/* can the available bitmap space cover the last agreed device size? */
	if (on_disk_bm_sect < (in_core->la_size_sect+7)/MD_4kB_SECT/8/512)
		goto err;

	return 0;

err:
	drbd_err(device, "meta data offsets don't make sense: idx=%d "
			"al_s=%u, al_sz4k=%u, al_offset=%d, bm_offset=%d, "
			"md_size_sect=%u, la_size=%llu, md_capacity=%llu\n",
			in_core->meta_dev_idx,
			in_core->al_stripes, in_core->al_stripe_size_4k,
			in_core->al_offset, in_core->bm_offset, in_core->md_size_sect,
			(unsigned long long)in_core->la_size_sect,
			(unsigned long long)capacity);

	return -EINVAL;
}