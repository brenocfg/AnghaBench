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
struct dmz_target {TYPE_1__* dev; } ;
struct dm_target {struct dmz_target* private; } ;
struct block_device {int dummy; } ;
struct TYPE_2__ {struct block_device* bdev; } ;

/* Variables and functions */

__attribute__((used)) static int dmz_prepare_ioctl(struct dm_target *ti, struct block_device **bdev)
{
	struct dmz_target *dmz = ti->private;

	*bdev = dmz->dev->bdev;

	return 0;
}