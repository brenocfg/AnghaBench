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
struct thin_c {TYPE_1__* origin_dev; int /*<<< orphan*/  origin_size; } ;
struct dm_target {struct thin_c* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_dev_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int thin_preresume(struct dm_target *ti)
{
	struct thin_c *tc = ti->private;

	if (tc->origin_dev)
		tc->origin_size = get_dev_size(tc->origin_dev->bdev);

	return 0;
}