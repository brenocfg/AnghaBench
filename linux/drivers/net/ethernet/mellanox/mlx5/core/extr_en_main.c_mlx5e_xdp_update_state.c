#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ xdp_prog; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct mlx5e_priv {TYPE_2__ channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_xdp_set_closed (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_xdp_set_open (struct mlx5e_priv*) ; 

__attribute__((used)) static int mlx5e_xdp_update_state(struct mlx5e_priv *priv)
{
	if (priv->channels.params.xdp_prog)
		mlx5e_xdp_set_open(priv);
	else
		mlx5e_xdp_set_closed(priv);

	return 0;
}