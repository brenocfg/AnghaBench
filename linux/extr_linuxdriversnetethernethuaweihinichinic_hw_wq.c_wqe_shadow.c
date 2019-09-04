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
struct hinic_wq {size_t num_q_pages; size_t max_wqe_size; int /*<<< orphan*/ * shadow_wqe; } ;
struct hinic_hw_wqe {int dummy; } ;

/* Variables and functions */
 int WQE_IN_RANGE (struct hinic_hw_wqe*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool wqe_shadow(struct hinic_wq *wq, struct hinic_hw_wqe *wqe)
{
	size_t wqe_shadow_size = wq->num_q_pages * wq->max_wqe_size;

	return WQE_IN_RANGE(wqe, wq->shadow_wqe,
			    &wq->shadow_wqe[wqe_shadow_size]);
}