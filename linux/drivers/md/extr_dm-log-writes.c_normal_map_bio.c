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
struct log_writes_c {TYPE_1__* dev; } ;
struct dm_target {struct log_writes_c* private; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void normal_map_bio(struct dm_target *ti, struct bio *bio)
{
	struct log_writes_c *lc = ti->private;

	bio_set_dev(bio, lc->dev->bdev);
}