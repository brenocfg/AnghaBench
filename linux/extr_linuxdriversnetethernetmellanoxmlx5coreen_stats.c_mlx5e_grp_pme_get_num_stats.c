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
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 int NUM_PME_ERR_STATS ; 
 int NUM_PME_STATUS_STATS ; 

__attribute__((used)) static int mlx5e_grp_pme_get_num_stats(struct mlx5e_priv *priv)
{
	return NUM_PME_STATUS_STATS + NUM_PME_ERR_STATS;
}