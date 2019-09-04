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
typedef  scalar_t__ u32 ;
struct hfi1_user_sdma_pkt_q {int /*<<< orphan*/  handler; } ;
struct evict_data {scalar_t__ cleared; scalar_t__ target; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi1_mmu_rb_evict (int /*<<< orphan*/ ,struct evict_data*) ; 

__attribute__((used)) static u32 sdma_cache_evict(struct hfi1_user_sdma_pkt_q *pq, u32 npages)
{
	struct evict_data evict_data;

	evict_data.cleared = 0;
	evict_data.target = npages;
	hfi1_mmu_rb_evict(pq->handler, &evict_data);
	return evict_data.cleared;
}