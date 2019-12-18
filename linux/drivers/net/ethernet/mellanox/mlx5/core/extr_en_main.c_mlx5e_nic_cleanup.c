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
struct mlx5e_priv {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_health_destroy_reporters (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_ipsec_cleanup (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_netdev_cleanup (int /*<<< orphan*/ ,struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_tls_cleanup (struct mlx5e_priv*) ; 

__attribute__((used)) static void mlx5e_nic_cleanup(struct mlx5e_priv *priv)
{
	mlx5e_health_destroy_reporters(priv);
	mlx5e_tls_cleanup(priv);
	mlx5e_ipsec_cleanup(priv);
	mlx5e_netdev_cleanup(priv->netdev, priv);
}