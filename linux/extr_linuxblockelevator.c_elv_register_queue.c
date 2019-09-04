#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  kobj; int /*<<< orphan*/  sysfs_lock; struct elevator_queue* elevator; } ;
struct TYPE_8__ {scalar_t__ name; } ;
struct elv_fs_entry {TYPE_4__ attr; } ;
struct elevator_queue {int registered; TYPE_3__* type; int /*<<< orphan*/  uses_mq; int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* elevator_registered_fn ) (struct request_queue*) ;} ;
struct TYPE_6__ {TYPE_1__ sq; } ;
struct TYPE_7__ {TYPE_2__ ops; struct elv_fs_entry* elevator_attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ADD ; 
 int kobject_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct request_queue*) ; 
 scalar_t__ sysfs_create_file (int /*<<< orphan*/ *,TYPE_4__*) ; 

int elv_register_queue(struct request_queue *q)
{
	struct elevator_queue *e = q->elevator;
	int error;

	lockdep_assert_held(&q->sysfs_lock);

	error = kobject_add(&e->kobj, &q->kobj, "%s", "iosched");
	if (!error) {
		struct elv_fs_entry *attr = e->type->elevator_attrs;
		if (attr) {
			while (attr->attr.name) {
				if (sysfs_create_file(&e->kobj, &attr->attr))
					break;
				attr++;
			}
		}
		kobject_uevent(&e->kobj, KOBJ_ADD);
		e->registered = 1;
		if (!e->uses_mq && e->type->ops.sq.elevator_registered_fn)
			e->type->ops.sq.elevator_registered_fn(q);
	}
	return error;
}