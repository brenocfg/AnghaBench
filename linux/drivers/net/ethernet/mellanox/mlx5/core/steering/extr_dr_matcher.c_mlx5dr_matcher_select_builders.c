#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5dr_matcher_rx_tx {int /*<<< orphan*/  num_of_builders; int /*<<< orphan*/  num_of_builders4; int /*<<< orphan*/  ste_builder4; int /*<<< orphan*/  ste_builder; int /*<<< orphan*/  num_of_builders6; int /*<<< orphan*/  ste_builder6; } ;
struct mlx5dr_matcher {TYPE_1__* tbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  dmn; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mlx5dr_dbg (int /*<<< orphan*/ ,char*) ; 

int mlx5dr_matcher_select_builders(struct mlx5dr_matcher *matcher,
				   struct mlx5dr_matcher_rx_tx *nic_matcher,
				   bool ipv6)
{
	if (ipv6) {
		nic_matcher->ste_builder = nic_matcher->ste_builder6;
		nic_matcher->num_of_builders = nic_matcher->num_of_builders6;
	} else {
		nic_matcher->ste_builder = nic_matcher->ste_builder4;
		nic_matcher->num_of_builders = nic_matcher->num_of_builders4;
	}

	if (!nic_matcher->num_of_builders) {
		mlx5dr_dbg(matcher->tbl->dmn,
			   "Rule not supported on this matcher due to IP related fields\n");
		return -EINVAL;
	}

	return 0;
}