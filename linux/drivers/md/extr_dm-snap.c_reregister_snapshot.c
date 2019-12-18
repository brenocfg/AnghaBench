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
struct dm_snapshot {int /*<<< orphan*/  list; TYPE_1__* origin; } ;
struct block_device {int dummy; } ;
struct TYPE_2__ {struct block_device* bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __insert_snapshot (int /*<<< orphan*/ ,struct dm_snapshot*) ; 
 int /*<<< orphan*/  __lookup_origin (struct block_device*) ; 
 int /*<<< orphan*/  _origins_lock ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reregister_snapshot(struct dm_snapshot *s)
{
	struct block_device *bdev = s->origin->bdev;

	down_write(&_origins_lock);

	list_del(&s->list);
	__insert_snapshot(__lookup_origin(bdev), s);

	up_write(&_origins_lock);
}