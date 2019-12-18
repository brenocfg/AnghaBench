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
typedef  int u64 ;
struct mlx5e_profile {int rq_groups; } ;
struct mlx5e_params {int num_channels; } ;

/* Variables and functions */

__attribute__((used)) static inline bool mlx5e_qid_validate(const struct mlx5e_profile *profile,
				      struct mlx5e_params *params, u64 qid)
{
	return qid < params->num_channels * profile->rq_groups;
}