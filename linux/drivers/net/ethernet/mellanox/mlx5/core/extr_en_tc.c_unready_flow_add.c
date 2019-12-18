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
struct mlx5e_tc_flow {int /*<<< orphan*/  unready; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOT_READY ; 
 int /*<<< orphan*/  flow_flag_set (struct mlx5e_tc_flow*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static void unready_flow_add(struct mlx5e_tc_flow *flow,
			     struct list_head *unready_flows)
{
	flow_flag_set(flow, NOT_READY);
	list_add_tail(&flow->unready, unready_flows);
}