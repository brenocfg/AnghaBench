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
struct dm_table {int num_targets; TYPE_2__* md; struct dm_target* targets; } ;
typedef  enum suspend_mode { ____Placeholder_suspend_mode } suspend_mode ;
struct TYPE_4__ {int /*<<< orphan*/  suspend_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* postsuspend ) (struct dm_target*) ;int /*<<< orphan*/  (* presuspend_undo ) (struct dm_target*) ;int /*<<< orphan*/  (* presuspend ) (struct dm_target*) ;} ;

/* Variables and functions */
#define  POSTSUSPEND 130 
#define  PRESUSPEND 129 
#define  PRESUSPEND_UNDO 128 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dm_target*) ; 
 int /*<<< orphan*/  stub2 (struct dm_target*) ; 
 int /*<<< orphan*/  stub3 (struct dm_target*) ; 

__attribute__((used)) static void suspend_targets(struct dm_table *t, enum suspend_mode mode)
{
	int i = t->num_targets;
	struct dm_target *ti = t->targets;

	lockdep_assert_held(&t->md->suspend_lock);

	while (i--) {
		switch (mode) {
		case PRESUSPEND:
			if (ti->type->presuspend)
				ti->type->presuspend(ti);
			break;
		case PRESUSPEND_UNDO:
			if (ti->type->presuspend_undo)
				ti->type->presuspend_undo(ti);
			break;
		case POSTSUSPEND:
			if (ti->type->postsuspend)
				ti->type->postsuspend(ti);
			break;
		}
		ti++;
	}
}