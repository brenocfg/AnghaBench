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
struct r5l_log {TYPE_1__* rdev; } ;
struct r5conf {int dummy; } ;
struct mddev {struct r5conf* private; } ;
struct TYPE_2__ {struct mddev* mddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  r5l_exit_log (struct r5conf*) ; 
 int r5l_load_log (struct r5l_log*) ; 

int r5l_start(struct r5l_log *log)
{
	int ret;

	if (!log)
		return 0;

	ret = r5l_load_log(log);
	if (ret) {
		struct mddev *mddev = log->rdev->mddev;
		struct r5conf *conf = mddev->private;

		r5l_exit_log(conf);
	}
	return ret;
}