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
struct thin_c {TYPE_2__* pool; TYPE_1__* pool_dev; } ;
struct dm_thin_new_mapping {int dummy; } ;
struct dm_io_region {void* count; void* sector; int /*<<< orphan*/  bdev; } ;
typedef  void* sector_t ;
struct TYPE_4__ {int /*<<< orphan*/  copier; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_complete ; 
 int /*<<< orphan*/  dm_kcopyd_zero (int /*<<< orphan*/ ,int,struct dm_io_region*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_thin_new_mapping*) ; 

__attribute__((used)) static void ll_zero(struct thin_c *tc, struct dm_thin_new_mapping *m,
		    sector_t begin, sector_t end)
{
	struct dm_io_region to;

	to.bdev = tc->pool_dev->bdev;
	to.sector = begin;
	to.count = end - begin;

	dm_kcopyd_zero(tc->pool->copier, 1, &to, 0, copy_complete, m);
}