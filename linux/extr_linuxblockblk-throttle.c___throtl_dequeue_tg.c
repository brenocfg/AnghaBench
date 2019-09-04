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
struct TYPE_2__ {int /*<<< orphan*/  parent_sq; } ;
struct throtl_grp {int /*<<< orphan*/  flags; TYPE_1__ service_queue; int /*<<< orphan*/  rb_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  THROTL_TG_PENDING ; 
 int /*<<< orphan*/  throtl_rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __throtl_dequeue_tg(struct throtl_grp *tg)
{
	throtl_rb_erase(&tg->rb_node, tg->service_queue.parent_sq);
	tg->flags &= ~THROTL_TG_PENDING;
}