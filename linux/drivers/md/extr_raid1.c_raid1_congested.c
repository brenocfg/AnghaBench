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
struct request_queue {int /*<<< orphan*/  backing_dev_info; } ;
struct r1conf {scalar_t__ pending_count; int raid_disks; TYPE_1__* mirrors; } ;
struct mddev {struct r1conf* private; } ;
struct md_rdev {int /*<<< orphan*/  bdev; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  Faulty ; 
 int WB_async_congested ; 
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int bdi_congested (int /*<<< orphan*/ ,int) ; 
 scalar_t__ max_queued_requests ; 
 struct md_rdev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raid1_congested(struct mddev *mddev, int bits)
{
	struct r1conf *conf = mddev->private;
	int i, ret = 0;

	if ((bits & (1 << WB_async_congested)) &&
	    conf->pending_count >= max_queued_requests)
		return 1;

	rcu_read_lock();
	for (i = 0; i < conf->raid_disks * 2; i++) {
		struct md_rdev *rdev = rcu_dereference(conf->mirrors[i].rdev);
		if (rdev && !test_bit(Faulty, &rdev->flags)) {
			struct request_queue *q = bdev_get_queue(rdev->bdev);

			BUG_ON(!q);

			/* Note the '|| 1' - when read_balance prefers
			 * non-congested targets, it can be removed
			 */
			if ((bits & (1 << WB_async_congested)) || 1)
				ret |= bdi_congested(q->backing_dev_info, bits);
			else
				ret &= bdi_congested(q->backing_dev_info, bits);
		}
	}
	rcu_read_unlock();
	return ret;
}