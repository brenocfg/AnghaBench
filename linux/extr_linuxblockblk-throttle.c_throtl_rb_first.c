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
struct throtl_service_queue {scalar_t__ first_pending; int /*<<< orphan*/  pending_tree; int /*<<< orphan*/  nr_pending; } ;
struct throtl_grp {int dummy; } ;

/* Variables and functions */
 struct throtl_grp* rb_entry_tg (scalar_t__) ; 
 scalar_t__ rb_first (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct throtl_grp *
throtl_rb_first(struct throtl_service_queue *parent_sq)
{
	/* Service tree is empty */
	if (!parent_sq->nr_pending)
		return NULL;

	if (!parent_sq->first_pending)
		parent_sq->first_pending = rb_first(&parent_sq->pending_tree);

	if (parent_sq->first_pending)
		return rb_entry_tg(parent_sq->first_pending);

	return NULL;
}