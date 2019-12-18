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
struct btree_write {int /*<<< orphan*/ * journal; scalar_t__ prio_blocked; } ;
struct btree {TYPE_2__* c; } ;
struct TYPE_3__ {int /*<<< orphan*/  wait; } ;
struct TYPE_4__ {TYPE_1__ journal; int /*<<< orphan*/  prio_blocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  __closure_wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec_bug (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub_return (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_allocators (TYPE_2__*) ; 

__attribute__((used)) static void btree_complete_write(struct btree *b, struct btree_write *w)
{
	if (w->prio_blocked &&
	    !atomic_sub_return(w->prio_blocked, &b->c->prio_blocked))
		wake_up_allocators(b->c);

	if (w->journal) {
		atomic_dec_bug(w->journal);
		__closure_wake_up(&b->c->journal.wait);
	}

	w->prio_blocked	= 0;
	w->journal	= NULL;
}