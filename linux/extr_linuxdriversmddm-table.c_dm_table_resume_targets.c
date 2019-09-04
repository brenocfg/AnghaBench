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
struct dm_target {TYPE_1__* type; } ;
struct dm_table {int num_targets; struct dm_target* targets; TYPE_2__* md; } ;
struct TYPE_4__ {int /*<<< orphan*/  suspend_lock; } ;
struct TYPE_3__ {int (* preresume ) (struct dm_target*) ;int /*<<< orphan*/  (* resume ) (struct dm_target*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dm_device_name (TYPE_2__*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int stub1 (struct dm_target*) ; 
 int /*<<< orphan*/  stub2 (struct dm_target*) ; 

int dm_table_resume_targets(struct dm_table *t)
{
	int i, r = 0;

	lockdep_assert_held(&t->md->suspend_lock);

	for (i = 0; i < t->num_targets; i++) {
		struct dm_target *ti = t->targets + i;

		if (!ti->type->preresume)
			continue;

		r = ti->type->preresume(ti);
		if (r) {
			DMERR("%s: %s: preresume failed, error = %d",
			      dm_device_name(t->md), ti->type->name, r);
			return r;
		}
	}

	for (i = 0; i < t->num_targets; i++) {
		struct dm_target *ti = t->targets + i;

		if (ti->type->resume)
			ti->type->resume(ti);
	}

	return 0;
}