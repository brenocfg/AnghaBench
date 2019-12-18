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
struct TYPE_2__ {int /*<<< orphan*/  cl; int /*<<< orphan*/  flags; } ;
struct cached_dev {TYPE_1__ disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCACHE_DEV_CLOSING ; 
 int /*<<< orphan*/  BCACHE_DEV_DETACHING ; 
 int /*<<< orphan*/  bch_register_lock ; 
 int /*<<< orphan*/  bch_writeback_queue (struct cached_dev*) ; 
 int /*<<< orphan*/  cached_dev_put (struct cached_dev*) ; 
 int /*<<< orphan*/  closure_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bch_cached_dev_detach(struct cached_dev *dc)
{
	lockdep_assert_held(&bch_register_lock);

	if (test_bit(BCACHE_DEV_CLOSING, &dc->disk.flags))
		return;

	if (test_and_set_bit(BCACHE_DEV_DETACHING, &dc->disk.flags))
		return;

	/*
	 * Block the device from being closed and freed until we're finished
	 * detaching
	 */
	closure_get(&dc->disk.cl);

	bch_writeback_queue(dc);

	cached_dev_put(dc);
}