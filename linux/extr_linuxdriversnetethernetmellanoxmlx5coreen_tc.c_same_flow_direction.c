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
struct mlx5e_tc_flow {int flags; } ;

/* Variables and functions */
 int DIRECTION_MASK ; 
 int FLOW_DIRECTION_MASK ; 

__attribute__((used)) static bool same_flow_direction(struct mlx5e_tc_flow *flow, int flags)
{
	if ((flow->flags & FLOW_DIRECTION_MASK) == (flags & DIRECTION_MASK))
		return true;

	return false;
}