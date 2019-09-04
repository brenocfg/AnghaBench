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
struct smq_policy {int /*<<< orphan*/  clean; int /*<<< orphan*/  dirty; } ;
struct entry {unsigned int level; } ;

/* Variables and functions */
 unsigned int NR_CACHE_LEVELS ; 
 struct entry* demote_sentinel (struct smq_policy*,unsigned int) ; 
 int /*<<< orphan*/  q_push (int /*<<< orphan*/ *,struct entry*) ; 
 struct entry* writeback_sentinel (struct smq_policy*,unsigned int) ; 

__attribute__((used)) static void __sentinels_init(struct smq_policy *mq)
{
	unsigned level;
	struct entry *sentinel;

	for (level = 0; level < NR_CACHE_LEVELS; level++) {
		sentinel = writeback_sentinel(mq, level);
		sentinel->level = level;
		q_push(&mq->dirty, sentinel);

		sentinel = demote_sentinel(mq, level);
		sentinel->level = level;
		q_push(&mq->clean, sentinel);
	}
}