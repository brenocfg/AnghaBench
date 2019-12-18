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
struct r5l_log {scalar_t__ r5c_journal_mode; int /*<<< orphan*/  disable_writeback_work; } ;
struct r5conf {struct r5l_log* log; } ;
struct mddev {struct r5conf* private; } ;
struct md_rdev {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  Journal ; 
 scalar_t__ R5C_JOURNAL_MODE_WRITE_BACK ; 
 scalar_t__ raid5_calc_degraded (struct r5conf*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void r5c_update_on_rdev_error(struct mddev *mddev, struct md_rdev *rdev)
{
	struct r5conf *conf = mddev->private;
	struct r5l_log *log = conf->log;

	if (!log)
		return;

	if ((raid5_calc_degraded(conf) > 0 ||
	     test_bit(Journal, &rdev->flags)) &&
	    conf->log->r5c_journal_mode == R5C_JOURNAL_MODE_WRITE_BACK)
		schedule_work(&log->disable_writeback_work);
}