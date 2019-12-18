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
typedef  int ssize_t ;
struct TYPE_2__ {int r5c_journal_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
#define  R5C_JOURNAL_MODE_WRITE_BACK 129 
#define  R5C_JOURNAL_MODE_WRITE_THROUGH 128 
 int mddev_lock (struct mddev*) ; 
 int /*<<< orphan*/  mddev_unlock (struct mddev*) ; 
 char** r5c_journal_mode_str ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static ssize_t r5c_journal_mode_show(struct mddev *mddev, char *page)
{
	struct r5conf *conf;
	int ret;

	ret = mddev_lock(mddev);
	if (ret)
		return ret;

	conf = mddev->private;
	if (!conf || !conf->log) {
		mddev_unlock(mddev);
		return 0;
	}

	switch (conf->log->r5c_journal_mode) {
	case R5C_JOURNAL_MODE_WRITE_THROUGH:
		ret = snprintf(
			page, PAGE_SIZE, "[%s] %s\n",
			r5c_journal_mode_str[R5C_JOURNAL_MODE_WRITE_THROUGH],
			r5c_journal_mode_str[R5C_JOURNAL_MODE_WRITE_BACK]);
		break;
	case R5C_JOURNAL_MODE_WRITE_BACK:
		ret = snprintf(
			page, PAGE_SIZE, "%s [%s]\n",
			r5c_journal_mode_str[R5C_JOURNAL_MODE_WRITE_THROUGH],
			r5c_journal_mode_str[R5C_JOURNAL_MODE_WRITE_BACK]);
		break;
	default:
		ret = 0;
	}
	mddev_unlock(mddev);
	return ret;
}