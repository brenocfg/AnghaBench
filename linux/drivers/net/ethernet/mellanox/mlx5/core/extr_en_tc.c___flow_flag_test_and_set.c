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
struct mlx5e_tc_flow {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int test_and_set_bit (unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __flow_flag_test_and_set(struct mlx5e_tc_flow *flow,
				     unsigned long flag)
{
	/* test_and_set_bit() provides all necessary barriers */
	return test_and_set_bit(flag, &flow->flags);
}