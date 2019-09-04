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
struct TYPE_4__ {struct cache_set* c; TYPE_1__* disk; int /*<<< orphan*/  flags; } ;
struct cached_dev {int io_disable; TYPE_2__ disk; int /*<<< orphan*/  backing_dev_name; } ;
struct cache_set {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCACHE_DEV_CLOSING ; 
 int /*<<< orphan*/  CACHE_SET_IO_DISABLE ; 
 int /*<<< orphan*/  bcache_device_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool bch_cached_dev_error(struct cached_dev *dc)
{
	struct cache_set *c;

	if (!dc || test_bit(BCACHE_DEV_CLOSING, &dc->disk.flags))
		return false;

	dc->io_disable = true;
	/* make others know io_disable is true earlier */
	smp_mb();

	pr_err("stop %s: too many IO errors on backing device %s\n",
		dc->disk.disk->disk_name, dc->backing_dev_name);

	/*
	 * If the cached device is still attached to a cache set,
	 * even dc->io_disable is true and no more I/O requests
	 * accepted, cache device internal I/O (writeback scan or
	 * garbage collection) may still prevent bcache device from
	 * being stopped. So here CACHE_SET_IO_DISABLE should be
	 * set to c->flags too, to make the internal I/O to cache
	 * device rejected and stopped immediately.
	 * If c is NULL, that means the bcache device is not attached
	 * to any cache set, then no CACHE_SET_IO_DISABLE bit to set.
	 */
	c = dc->disk.c;
	if (c && test_and_set_bit(CACHE_SET_IO_DISABLE, &c->flags))
		pr_info("CACHE_SET_IO_DISABLE already set");

	bcache_device_stop(&dc->disk);
	return true;
}