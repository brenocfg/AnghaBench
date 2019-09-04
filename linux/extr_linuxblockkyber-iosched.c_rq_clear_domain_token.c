#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request {TYPE_1__* mq_ctx; int /*<<< orphan*/  cmd_flags; } ;
struct kyber_queue_data {int /*<<< orphan*/ * domain_tokens; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 unsigned int kyber_sched_domain (int /*<<< orphan*/ ) ; 
 int rq_get_domain_token (struct request*) ; 
 int /*<<< orphan*/  sbitmap_queue_clear (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rq_clear_domain_token(struct kyber_queue_data *kqd,
				  struct request *rq)
{
	unsigned int sched_domain;
	int nr;

	nr = rq_get_domain_token(rq);
	if (nr != -1) {
		sched_domain = kyber_sched_domain(rq->cmd_flags);
		sbitmap_queue_clear(&kqd->domain_tokens[sched_domain], nr,
				    rq->mq_ctx->cpu);
	}
}