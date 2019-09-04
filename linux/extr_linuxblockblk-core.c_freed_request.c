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
struct request_queue {int /*<<< orphan*/  nr_rqs_elvpriv; int /*<<< orphan*/ * nr_rqs; } ;
struct request_list {int /*<<< orphan*/ * starved; int /*<<< orphan*/ * count; struct request_queue* q; } ;
typedef  int req_flags_t ;

/* Variables and functions */
 int RQF_ELVPRIV ; 
 int /*<<< orphan*/  __freed_request (struct request_list*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void freed_request(struct request_list *rl, bool sync,
		req_flags_t rq_flags)
{
	struct request_queue *q = rl->q;

	q->nr_rqs[sync]--;
	rl->count[sync]--;
	if (rq_flags & RQF_ELVPRIV)
		q->nr_rqs_elvpriv--;

	__freed_request(rl, sync);

	if (unlikely(rl->starved[sync ^ 1]))
		__freed_request(rl, sync ^ 1);
}