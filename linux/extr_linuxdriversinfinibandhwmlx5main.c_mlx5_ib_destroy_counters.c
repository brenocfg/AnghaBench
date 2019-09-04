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
struct mlx5_ib_mcounters {scalar_t__ hw_cntrs_hndl; } ;
struct ib_counters {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  counters_clear_description (struct ib_counters*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_mcounters*) ; 
 int /*<<< orphan*/  mlx5_fc_destroy (int /*<<< orphan*/ ,scalar_t__) ; 
 struct mlx5_ib_mcounters* to_mcounters (struct ib_counters*) ; 
 TYPE_1__* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_ib_destroy_counters(struct ib_counters *counters)
{
	struct mlx5_ib_mcounters *mcounters = to_mcounters(counters);

	counters_clear_description(counters);
	if (mcounters->hw_cntrs_hndl)
		mlx5_fc_destroy(to_mdev(counters->device)->mdev,
				mcounters->hw_cntrs_hndl);

	kfree(mcounters);

	return 0;
}