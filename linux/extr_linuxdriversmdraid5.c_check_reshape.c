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
struct r5conf {scalar_t__ previous_raid_disks; scalar_t__ pool_size; } ;
struct mddev {scalar_t__ delta_disks; scalar_t__ new_layout; scalar_t__ layout; scalar_t__ new_chunk_sectors; scalar_t__ chunk_sectors; scalar_t__ reshape_position; int level; int raid_disks; struct r5conf* private; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  check_stripe_cache (struct mddev*) ; 
 scalar_t__ has_failed (struct r5conf*) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ raid5_has_log (struct r5conf*) ; 
 scalar_t__ raid5_has_ppl (struct r5conf*) ; 
 scalar_t__ resize_chunks (struct r5conf*,scalar_t__,scalar_t__) ; 
 int resize_stripes (struct r5conf*,scalar_t__) ; 

__attribute__((used)) static int check_reshape(struct mddev *mddev)
{
	struct r5conf *conf = mddev->private;

	if (raid5_has_log(conf) || raid5_has_ppl(conf))
		return -EINVAL;
	if (mddev->delta_disks == 0 &&
	    mddev->new_layout == mddev->layout &&
	    mddev->new_chunk_sectors == mddev->chunk_sectors)
		return 0; /* nothing to do */
	if (has_failed(conf))
		return -EINVAL;
	if (mddev->delta_disks < 0 && mddev->reshape_position == MaxSector) {
		/* We might be able to shrink, but the devices must
		 * be made bigger first.
		 * For raid6, 4 is the minimum size.
		 * Otherwise 2 is the minimum
		 */
		int min = 2;
		if (mddev->level == 6)
			min = 4;
		if (mddev->raid_disks + mddev->delta_disks < min)
			return -EINVAL;
	}

	if (!check_stripe_cache(mddev))
		return -ENOSPC;

	if (mddev->new_chunk_sectors > mddev->chunk_sectors ||
	    mddev->delta_disks > 0)
		if (resize_chunks(conf,
				  conf->previous_raid_disks
				  + max(0, mddev->delta_disks),
				  max(mddev->new_chunk_sectors,
				      mddev->chunk_sectors)
			    ) < 0)
			return -ENOMEM;

	if (conf->previous_raid_disks + mddev->delta_disks <= conf->pool_size)
		return 0; /* never bother to shrink */
	return resize_stripes(conf, (conf->previous_raid_disks
				     + mddev->delta_disks));
}