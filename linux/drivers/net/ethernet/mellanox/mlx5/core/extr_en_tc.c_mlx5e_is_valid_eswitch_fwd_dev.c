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
struct net_device {int dummy; } ;
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_merged_eswitch_dev (struct mlx5e_priv*,struct net_device*) ; 
 scalar_t__ mlx5e_eswitch_rep (struct net_device*) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 scalar_t__ same_hw_devs (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 

bool mlx5e_is_valid_eswitch_fwd_dev(struct mlx5e_priv *priv,
				    struct net_device *out_dev)
{
	if (is_merged_eswitch_dev(priv, out_dev))
		return true;

	return mlx5e_eswitch_rep(out_dev) &&
	       same_hw_devs(priv, netdev_priv(out_dev));
}