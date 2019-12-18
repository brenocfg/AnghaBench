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
struct closure_waitlist {int /*<<< orphan*/  list; } ;
struct closure {int /*<<< orphan*/  list; int /*<<< orphan*/  remaining; } ;

/* Variables and functions */
 int CLOSURE_WAITING ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closure_set_waiting (struct closure*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool closure_wait(struct closure_waitlist *waitlist, struct closure *cl)
{
	if (atomic_read(&cl->remaining) & CLOSURE_WAITING)
		return false;

	closure_set_waiting(cl, _RET_IP_);
	atomic_add(CLOSURE_WAITING + 1, &cl->remaining);
	llist_add(&cl->list, &waitlist->list);

	return true;
}