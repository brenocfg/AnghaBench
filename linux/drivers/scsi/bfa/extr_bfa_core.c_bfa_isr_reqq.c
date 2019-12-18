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
struct list_head {int dummy; } ;
struct bfa_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_isr_reqq_ack (struct bfa_s*,int) ; 
 struct list_head* bfa_reqq (struct bfa_s*,int) ; 
 int /*<<< orphan*/  bfa_reqq_resume (struct bfa_s*,int) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 

__attribute__((used)) static inline void
bfa_isr_reqq(struct bfa_s *bfa, int qid)
{
	struct list_head *waitq;

	bfa_isr_reqq_ack(bfa, qid);

	/*
	 * Resume any pending requests in the corresponding reqq.
	 */
	waitq = bfa_reqq(bfa, qid);
	if (!list_empty(waitq))
		bfa_reqq_resume(bfa, qid);
}