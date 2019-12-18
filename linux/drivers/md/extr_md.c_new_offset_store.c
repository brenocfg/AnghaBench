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
struct mddev {unsigned long long dev_sectors; int reshape_backwards; size_t major_version; scalar_t__ persistent; scalar_t__ pers; int /*<<< orphan*/  recovery; scalar_t__ sync_thread; } ;
struct md_rdev {unsigned long long data_offset; unsigned long long sectors; unsigned long long new_data_offset; struct mddev* mddev; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* allow_new_offset ) (struct md_rdev*,unsigned long long) ;} ;

/* Variables and functions */
 size_t E2BIG ; 
 size_t EBUSY ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  MD_RECOVERY_RUNNING ; 
 scalar_t__ kstrtoull (char const*,int,unsigned long long*) ; 
 int /*<<< orphan*/  stub1 (struct md_rdev*,unsigned long long) ; 
 TYPE_1__* super_types ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t new_offset_store(struct md_rdev *rdev,
				const char *buf, size_t len)
{
	unsigned long long new_offset;
	struct mddev *mddev = rdev->mddev;

	if (kstrtoull(buf, 10, &new_offset) < 0)
		return -EINVAL;

	if (mddev->sync_thread ||
	    test_bit(MD_RECOVERY_RUNNING,&mddev->recovery))
		return -EBUSY;
	if (new_offset == rdev->data_offset)
		/* reset is always permitted */
		;
	else if (new_offset > rdev->data_offset) {
		/* must not push array size beyond rdev_sectors */
		if (new_offset - rdev->data_offset
		    + mddev->dev_sectors > rdev->sectors)
				return -E2BIG;
	}
	/* Metadata worries about other space details. */

	/* decreasing the offset is inconsistent with a backwards
	 * reshape.
	 */
	if (new_offset < rdev->data_offset &&
	    mddev->reshape_backwards)
		return -EINVAL;
	/* Increasing offset is inconsistent with forwards
	 * reshape.  reshape_direction should be set to
	 * 'backwards' first.
	 */
	if (new_offset > rdev->data_offset &&
	    !mddev->reshape_backwards)
		return -EINVAL;

	if (mddev->pers && mddev->persistent &&
	    !super_types[mddev->major_version]
	    .allow_new_offset(rdev, new_offset))
		return -E2BIG;
	rdev->new_data_offset = new_offset;
	if (new_offset > rdev->data_offset)
		mddev->reshape_backwards = 1;
	else if (new_offset < rdev->data_offset)
		mddev->reshape_backwards = 0;

	return len;
}