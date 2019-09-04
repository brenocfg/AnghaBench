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
struct mlx4_qp_table {int /*<<< orphan*/  zones; } ;
struct mlx4_priv {struct mlx4_qp_table qp_table; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ mlx4_is_qp_reserved (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_zone_free_entries_unique (int /*<<< orphan*/ ,int,int) ; 

void __mlx4_qp_release_range(struct mlx4_dev *dev, int base_qpn, int cnt)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_qp_table *qp_table = &priv->qp_table;

	if (mlx4_is_qp_reserved(dev, (u32) base_qpn))
		return;
	mlx4_zone_free_entries_unique(qp_table->zones, base_qpn, cnt);
}