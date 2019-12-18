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
struct page {int dummy; } ;
struct md_rdev {TYPE_1__* mddev; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  recovery; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int WRITE ; 
 int /*<<< orphan*/  WantReplacement ; 
 int /*<<< orphan*/  WriteErrorSeen ; 
 int /*<<< orphan*/  md_error (TYPE_1__*,struct md_rdev*) ; 
 int /*<<< orphan*/  rdev_set_badblocks (struct md_rdev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sync_page_io (struct md_rdev*,int /*<<< orphan*/ ,int,struct page*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r1_sync_page_io(struct md_rdev *rdev, sector_t sector,
			    int sectors, struct page *page, int rw)
{
	if (sync_page_io(rdev, sector, sectors << 9, page, rw, 0, false))
		/* success */
		return 1;
	if (rw == WRITE) {
		set_bit(WriteErrorSeen, &rdev->flags);
		if (!test_and_set_bit(WantReplacement,
				      &rdev->flags))
			set_bit(MD_RECOVERY_NEEDED, &
				rdev->mddev->recovery);
	}
	/* need to record an error - either for the block or the device */
	if (!rdev_set_badblocks(rdev, sector, sectors, 0))
		md_error(rdev->mddev, rdev);
	return 0;
}