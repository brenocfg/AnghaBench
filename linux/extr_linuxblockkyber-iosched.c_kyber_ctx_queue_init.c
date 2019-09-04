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
struct kyber_ctx_queue {int /*<<< orphan*/ * rq_list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int KYBER_NUM_DOMAINS ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kyber_ctx_queue_init(struct kyber_ctx_queue *kcq)
{
	unsigned int i;

	spin_lock_init(&kcq->lock);
	for (i = 0; i < KYBER_NUM_DOMAINS; i++)
		INIT_LIST_HEAD(&kcq->rq_list[i]);
}