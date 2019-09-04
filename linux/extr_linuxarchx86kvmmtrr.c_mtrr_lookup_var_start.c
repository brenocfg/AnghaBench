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
struct mtrr_iter {int fixed; int /*<<< orphan*/ * range; int /*<<< orphan*/  start; int /*<<< orphan*/  start_max; struct kvm_mtrr* mtrr_state; } ;
struct kvm_mtrr {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mtrr_lookup_var_next (struct mtrr_iter*) ; 
 int /*<<< orphan*/ * list_prepare_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node ; 

__attribute__((used)) static void mtrr_lookup_var_start(struct mtrr_iter *iter)
{
	struct kvm_mtrr *mtrr_state = iter->mtrr_state;

	iter->fixed = false;
	iter->start_max = iter->start;
	iter->range = NULL;
	iter->range = list_prepare_entry(iter->range, &mtrr_state->head, node);

	__mtrr_lookup_var_next(iter);
}