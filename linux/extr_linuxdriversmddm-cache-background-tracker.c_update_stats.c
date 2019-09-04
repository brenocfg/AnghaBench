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
struct policy_work {int op; } ;
struct background_tracker {int /*<<< orphan*/  pending_writebacks; int /*<<< orphan*/  pending_demotes; int /*<<< orphan*/  pending_promotes; } ;

/* Variables and functions */
#define  POLICY_DEMOTE 130 
#define  POLICY_PROMOTE 129 
#define  POLICY_WRITEBACK 128 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_stats(struct background_tracker *b, struct policy_work *w, int delta)
{
	switch (w->op) {
	case POLICY_PROMOTE:
		atomic_add(delta, &b->pending_promotes);
		break;

	case POLICY_DEMOTE:
		atomic_add(delta, &b->pending_demotes);
		break;

	case POLICY_WRITEBACK:
		atomic_add(delta, &b->pending_writebacks);
		break;
	}
}