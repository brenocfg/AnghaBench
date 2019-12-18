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
struct bcache_device {int /*<<< orphan*/  cl; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCACHE_DEV_CLOSING ; 
 int /*<<< orphan*/  closure_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bcache_device_stop(struct bcache_device *d)
{
	if (!test_and_set_bit(BCACHE_DEV_CLOSING, &d->flags))
		/*
		 * closure_fn set to
		 * - cached device: cached_dev_flush()
		 * - flash dev: flash_dev_flush()
		 */
		closure_queue(&d->cl);
}