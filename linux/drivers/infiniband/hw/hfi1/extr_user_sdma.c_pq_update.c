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
struct hfi1_user_sdma_pkt_q {int /*<<< orphan*/  wait; int /*<<< orphan*/  n_reqs; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void pq_update(struct hfi1_user_sdma_pkt_q *pq)
{
	if (atomic_dec_and_test(&pq->n_reqs))
		wake_up(&pq->wait);
}