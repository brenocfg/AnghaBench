#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct r5l_log {TYPE_2__* rdev; } ;
struct r5conf {TYPE_1__* mddev; int /*<<< orphan*/  log; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  MD_HAS_JOURNAL ; 
 struct r5l_log* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool r5l_log_disk_error(struct r5conf *conf)
{
	struct r5l_log *log;
	bool ret;
	/* don't allow write if journal disk is missing */
	rcu_read_lock();
	log = rcu_dereference(conf->log);

	if (!log)
		ret = test_bit(MD_HAS_JOURNAL, &conf->mddev->flags);
	else
		ret = test_bit(Faulty, &log->rdev->flags);
	rcu_read_unlock();
	return ret;
}