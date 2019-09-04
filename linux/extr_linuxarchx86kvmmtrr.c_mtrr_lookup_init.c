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
typedef  void* u64 ;
struct mtrr_iter {int mtrr_disabled; int partial_map; int fixed; int /*<<< orphan*/ * range; void* end; void* start; struct kvm_mtrr* mtrr_state; } ;
struct kvm_mtrr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtrr_lookup_start (struct mtrr_iter*) ; 

__attribute__((used)) static void mtrr_lookup_init(struct mtrr_iter *iter,
			     struct kvm_mtrr *mtrr_state, u64 start, u64 end)
{
	iter->mtrr_state = mtrr_state;
	iter->start = start;
	iter->end = end;
	iter->mtrr_disabled = false;
	iter->partial_map = false;
	iter->fixed = false;
	iter->range = NULL;

	mtrr_lookup_start(iter);
}