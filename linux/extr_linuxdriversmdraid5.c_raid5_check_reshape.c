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
struct r5conf {scalar_t__ algorithm; int chunk_sectors; } ;
struct mddev {int new_chunk_sectors; scalar_t__ new_layout; int array_sectors; int raid_disks; scalar_t__ layout; int chunk_sectors; int /*<<< orphan*/  thread; int /*<<< orphan*/  sb_flags; struct r5conf* private; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MD_SB_CHANGE_DEVS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  algorithm_valid_raid5 (scalar_t__) ; 
 int check_reshape (struct mddev*) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raid5_check_reshape(struct mddev *mddev)
{
	/* For a 2-drive array, the layout and chunk size can be changed
	 * immediately as not restriping is needed.
	 * For larger arrays we record the new value - after validation
	 * to be used by a reshape pass.
	 */
	struct r5conf *conf = mddev->private;
	int new_chunk = mddev->new_chunk_sectors;

	if (mddev->new_layout >= 0 && !algorithm_valid_raid5(mddev->new_layout))
		return -EINVAL;
	if (new_chunk > 0) {
		if (!is_power_of_2(new_chunk))
			return -EINVAL;
		if (new_chunk < (PAGE_SIZE>>9))
			return -EINVAL;
		if (mddev->array_sectors & (new_chunk-1))
			/* not factor of array size */
			return -EINVAL;
	}

	/* They look valid */

	if (mddev->raid_disks == 2) {
		/* can make the change immediately */
		if (mddev->new_layout >= 0) {
			conf->algorithm = mddev->new_layout;
			mddev->layout = mddev->new_layout;
		}
		if (new_chunk > 0) {
			conf->chunk_sectors = new_chunk ;
			mddev->chunk_sectors = new_chunk;
		}
		set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
		md_wakeup_thread(mddev->thread);
	}
	return check_reshape(mddev);
}