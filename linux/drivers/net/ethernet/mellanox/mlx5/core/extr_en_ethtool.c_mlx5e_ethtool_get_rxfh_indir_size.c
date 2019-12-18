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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_INDIR_RQT_SIZE ; 

u32 mlx5e_ethtool_get_rxfh_indir_size(struct mlx5e_priv *priv)
{
	return MLX5E_INDIR_RQT_SIZE;
}