#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct throtl_service_queue {int /*<<< orphan*/  first_pending_disptime; } ;
struct throtl_grp {int /*<<< orphan*/  disptime; } ;

/* Variables and functions */
 struct throtl_grp* throtl_rb_first (struct throtl_service_queue*) ; 

__attribute__((used)) static void update_min_dispatch_time(struct throtl_service_queue *parent_sq)
{
	struct throtl_grp *tg;

	tg = throtl_rb_first(parent_sq);
	if (!tg)
		return;

	parent_sq->first_pending_disptime = tg->disptime;
}