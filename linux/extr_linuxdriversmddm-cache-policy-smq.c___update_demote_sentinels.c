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
struct queue {unsigned int nr_levels; } ;
struct smq_policy {struct queue clean; } ;
struct entry {int dummy; } ;

/* Variables and functions */
 struct entry* demote_sentinel (struct smq_policy*,unsigned int) ; 
 int /*<<< orphan*/  q_del (struct queue*,struct entry*) ; 
 int /*<<< orphan*/  q_push (struct queue*,struct entry*) ; 

__attribute__((used)) static void __update_demote_sentinels(struct smq_policy *mq)
{
	unsigned level;
	struct queue *q = &mq->clean;
	struct entry *sentinel;

	for (level = 0; level < q->nr_levels; level++) {
		sentinel = demote_sentinel(mq, level);
		q_del(q, sentinel);
		q_push(q, sentinel);
	}
}