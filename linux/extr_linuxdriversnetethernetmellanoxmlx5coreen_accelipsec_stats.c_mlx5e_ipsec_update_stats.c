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
typedef  int /*<<< orphan*/  u64 ;
struct mlx5e_priv {TYPE_1__* ipsec; int /*<<< orphan*/  mdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUM_IPSEC_HW_COUNTERS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlx5_accel_ipsec_counters_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mlx5e_ipsec_update_stats(struct mlx5e_priv *priv)
{
	int ret;

	if (!priv->ipsec)
		return;

	ret = mlx5_accel_ipsec_counters_read(priv->mdev, (u64 *)&priv->ipsec->stats,
					     NUM_IPSEC_HW_COUNTERS);
	if (ret)
		memset(&priv->ipsec->stats, 0, sizeof(priv->ipsec->stats));
}