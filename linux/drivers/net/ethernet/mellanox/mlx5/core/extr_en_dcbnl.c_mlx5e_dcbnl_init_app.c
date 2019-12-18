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
 int /*<<< orphan*/  INIT ; 
 int /*<<< orphan*/  mlx5e_dcbnl_dscp_app (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 

void mlx5e_dcbnl_init_app(struct mlx5e_priv *priv)
{
	mlx5e_dcbnl_dscp_app(priv, INIT);
}