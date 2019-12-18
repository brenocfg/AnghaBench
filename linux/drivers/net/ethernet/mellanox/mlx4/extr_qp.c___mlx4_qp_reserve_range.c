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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx4_qp_table {int /*<<< orphan*/  zones; } ;
struct mlx4_priv {struct mlx4_qp_table qp_table; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MLX4_BF_QP_SKIP_MASK ; 
 int MLX4_MAX_BF_QP_RANGE ; 
 int /*<<< orphan*/  MLX4_QP_TABLE_ZONE_GENERAL ; 
 int /*<<< orphan*/  MLX4_QP_TABLE_ZONE_RAW_ETH ; 
 int /*<<< orphan*/  MLX4_QP_TABLE_ZONE_RSS ; 
 scalar_t__ MLX4_RESERVE_A0_QP ; 
 scalar_t__ MLX4_RESERVE_ETH_BF_QP ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_zone_alloc_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int __mlx4_qp_reserve_range(struct mlx4_dev *dev, int cnt, int align,
			    int *base, u8 flags)
{
	u32 uid;
	int bf_qp = !!(flags & (u8)MLX4_RESERVE_ETH_BF_QP);

	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_qp_table *qp_table = &priv->qp_table;

	if (cnt > MLX4_MAX_BF_QP_RANGE && bf_qp)
		return -ENOMEM;

	uid = MLX4_QP_TABLE_ZONE_GENERAL;
	if (flags & (u8)MLX4_RESERVE_A0_QP) {
		if (bf_qp)
			uid = MLX4_QP_TABLE_ZONE_RAW_ETH;
		else
			uid = MLX4_QP_TABLE_ZONE_RSS;
	}

	*base = mlx4_zone_alloc_entries(qp_table->zones, uid, cnt, align,
					bf_qp ? MLX4_BF_QP_SKIP_MASK : 0, NULL);
	if (*base == -1)
		return -ENOMEM;

	return 0;
}