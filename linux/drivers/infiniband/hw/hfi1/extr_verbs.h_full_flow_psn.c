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
typedef  int /*<<< orphan*/  u32 ;
struct tid_rdma_flow {int /*<<< orphan*/  flow_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __full_flow_psn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 full_flow_psn(struct tid_rdma_flow *flow, u32 psn)
{
	return __full_flow_psn(&flow->flow_state, psn);
}