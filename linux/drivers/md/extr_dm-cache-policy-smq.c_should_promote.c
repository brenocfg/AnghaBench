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
struct smq_policy {scalar_t__ write_promote_level; scalar_t__ read_promote_level; int /*<<< orphan*/  cache_alloc; } ;
struct entry {scalar_t__ level; } ;
typedef  enum promote_result { ____Placeholder_promote_result } promote_result ;

/* Variables and functions */
 int PROMOTE_TEMPORARY ; 
 int WRITE ; 
 int /*<<< orphan*/  allocator_empty (int /*<<< orphan*/ *) ; 
 int maybe_promote (int) ; 

__attribute__((used)) static enum promote_result should_promote(struct smq_policy *mq, struct entry *hs_e,
					  int data_dir, bool fast_promote)
{
	if (data_dir == WRITE) {
		if (!allocator_empty(&mq->cache_alloc) && fast_promote)
			return PROMOTE_TEMPORARY;

		return maybe_promote(hs_e->level >= mq->write_promote_level);
	} else
		return maybe_promote(hs_e->level >= mq->read_promote_level);
}