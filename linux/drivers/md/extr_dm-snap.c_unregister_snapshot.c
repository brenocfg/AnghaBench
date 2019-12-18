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
struct origin {int /*<<< orphan*/  hash_list; int /*<<< orphan*/  snapshots; } ;
struct dm_snapshot {int /*<<< orphan*/  list; TYPE_1__* origin; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 struct origin* __lookup_origin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _origins_lock ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct origin*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unregister_snapshot(struct dm_snapshot *s)
{
	struct origin *o;

	down_write(&_origins_lock);
	o = __lookup_origin(s->origin->bdev);

	list_del(&s->list);
	if (o && list_empty(&o->snapshots)) {
		list_del(&o->hash_list);
		kfree(o);
	}

	up_write(&_origins_lock);
}