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
struct mlx5e_priv {int /*<<< orphan*/  mdev; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int mlx5e_port_linkspeed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_test_link_speed(struct mlx5e_priv *priv)
{
	u32 speed;

	if (!netif_carrier_ok(priv->netdev))
		return 1;

	return mlx5e_port_linkspeed(priv->mdev, &speed);
}