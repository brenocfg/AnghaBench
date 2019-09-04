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
struct rq_qos {struct rq_qos* next; } ;
struct request_queue {struct rq_qos* rq_qos; } ;

/* Variables and functions */

__attribute__((used)) static inline void rq_qos_del(struct request_queue *q, struct rq_qos *rqos)
{
	struct rq_qos *cur, *prev = NULL;
	for (cur = q->rq_qos; cur; cur = cur->next) {
		if (cur == rqos) {
			if (prev)
				prev->next = rqos->next;
			else
				q->rq_qos = cur;
			break;
		}
		prev = cur;
	}
}