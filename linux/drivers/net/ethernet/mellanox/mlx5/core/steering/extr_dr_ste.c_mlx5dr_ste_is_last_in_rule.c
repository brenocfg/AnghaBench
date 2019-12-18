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
typedef  scalar_t__ u8 ;
struct mlx5dr_matcher_rx_tx {scalar_t__ num_of_builders; } ;

/* Variables and functions */

bool mlx5dr_ste_is_last_in_rule(struct mlx5dr_matcher_rx_tx *nic_matcher,
				u8 ste_location)
{
	return ste_location == nic_matcher->num_of_builders;
}