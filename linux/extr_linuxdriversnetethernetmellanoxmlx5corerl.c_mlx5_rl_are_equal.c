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
struct mlx5_rate_limit {scalar_t__ rate; scalar_t__ max_burst_sz; scalar_t__ typical_pkt_sz; } ;

/* Variables and functions */

bool mlx5_rl_are_equal(struct mlx5_rate_limit *rl_0,
		       struct mlx5_rate_limit *rl_1)
{
	return ((rl_0->rate == rl_1->rate) &&
		(rl_0->max_burst_sz == rl_1->max_burst_sz) &&
		(rl_0->typical_pkt_sz == rl_1->typical_pkt_sz));
}