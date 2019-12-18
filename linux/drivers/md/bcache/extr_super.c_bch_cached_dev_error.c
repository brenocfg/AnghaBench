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
struct TYPE_4__ {TYPE_1__* disk; int /*<<< orphan*/  flags; } ;
struct cached_dev {int io_disable; TYPE_2__ disk; int /*<<< orphan*/  backing_dev_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCACHE_DEV_CLOSING ; 
 int /*<<< orphan*/  bcache_device_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool bch_cached_dev_error(struct cached_dev *dc)
{
	if (!dc || test_bit(BCACHE_DEV_CLOSING, &dc->disk.flags))
		return false;

	dc->io_disable = true;
	/* make others know io_disable is true earlier */
	smp_mb();

	pr_err("stop %s: too many IO errors on backing device %s\n",
		dc->disk.disk->disk_name, dc->backing_dev_name);

	bcache_device_stop(&dc->disk);
	return true;
}