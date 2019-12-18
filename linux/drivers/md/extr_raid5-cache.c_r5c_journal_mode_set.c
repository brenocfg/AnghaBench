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
struct r5conf {TYPE_1__* log; } ;
struct mddev {struct r5conf* private; } ;
struct TYPE_2__ {int r5c_journal_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int R5C_JOURNAL_MODE_WRITE_BACK ; 
 int R5C_JOURNAL_MODE_WRITE_THROUGH ; 
 int /*<<< orphan*/  mddev_resume (struct mddev*) ; 
 int /*<<< orphan*/  mddev_suspend (struct mddev*) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r5c_journal_mode_str ; 
 scalar_t__ raid5_calc_degraded (struct r5conf*) ; 

int r5c_journal_mode_set(struct mddev *mddev, int mode)
{
	struct r5conf *conf;

	if (mode < R5C_JOURNAL_MODE_WRITE_THROUGH ||
	    mode > R5C_JOURNAL_MODE_WRITE_BACK)
		return -EINVAL;

	conf = mddev->private;
	if (!conf || !conf->log)
		return -ENODEV;

	if (raid5_calc_degraded(conf) > 0 &&
	    mode == R5C_JOURNAL_MODE_WRITE_BACK)
		return -EINVAL;

	mddev_suspend(mddev);
	conf->log->r5c_journal_mode = mode;
	mddev_resume(mddev);

	pr_debug("md/raid:%s: setting r5c cache mode to %d: %s\n",
		 mdname(mddev), mode, r5c_journal_mode_str[mode]);
	return 0;
}