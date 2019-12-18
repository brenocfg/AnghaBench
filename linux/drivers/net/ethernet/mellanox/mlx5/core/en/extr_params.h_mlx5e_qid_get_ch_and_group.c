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
typedef  int u16 ;
struct mlx5e_params {int num_channels; } ;
typedef  enum mlx5e_rq_group { ____Placeholder_mlx5e_rq_group } mlx5e_rq_group ;

/* Variables and functions */

__attribute__((used)) static inline void mlx5e_qid_get_ch_and_group(struct mlx5e_params *params,
					      u16 qid,
					      u16 *ix,
					      enum mlx5e_rq_group *group)
{
	u16 nch = params->num_channels;

	*ix = qid % nch;
	*group = qid / nch;
}