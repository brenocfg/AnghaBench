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
struct TYPE_2__ {scalar_t__ mode; } ;
struct raid_set {int /*<<< orphan*/  runtime_flags; TYPE_1__ journal_dev; } ;
struct md_rdev {int /*<<< orphan*/  flags; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  Journal ; 
 scalar_t__ R5C_JOURNAL_MODE_WRITE_THROUGH ; 
 int /*<<< orphan*/  RT_FLAG_RS_IN_SYNC ; 
 int /*<<< orphan*/  RT_FLAG_RS_RESYNCING ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *__raid_dev_status(struct raid_set *rs, struct md_rdev *rdev)
{
	if (!rdev->bdev)
		return "-";
	else if (test_bit(Faulty, &rdev->flags))
		return "D";
	else if (test_bit(Journal, &rdev->flags))
		return (rs->journal_dev.mode == R5C_JOURNAL_MODE_WRITE_THROUGH) ? "A" : "a";
	else if (test_bit(RT_FLAG_RS_RESYNCING, &rs->runtime_flags) ||
		 (!test_bit(RT_FLAG_RS_IN_SYNC, &rs->runtime_flags) &&
		  !test_bit(In_sync, &rdev->flags)))
		return "a";
	else
		return "A";
}