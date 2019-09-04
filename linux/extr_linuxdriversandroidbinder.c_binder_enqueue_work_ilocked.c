#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct TYPE_3__ {scalar_t__ next; } ;
struct binder_work {TYPE_1__ entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  list_add_tail (TYPE_1__*,struct list_head*) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 

__attribute__((used)) static void
binder_enqueue_work_ilocked(struct binder_work *work,
			   struct list_head *target_list)
{
	BUG_ON(target_list == NULL);
	BUG_ON(work->entry.next && !list_empty(&work->entry));
	list_add_tail(&work->entry, target_list);
}