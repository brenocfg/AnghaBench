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
struct TYPE_2__ {int /*<<< orphan*/  params; } ;
struct mlx5e_priv {TYPE_1__ channels; } ;
struct mlx5e_channels {int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int mlx5e_safe_switch_channels (struct mlx5e_priv*,struct mlx5e_channels*,int /*<<< orphan*/ *) ; 

int mlx5e_safe_reopen_channels(struct mlx5e_priv *priv)
{
	struct mlx5e_channels new_channels = {};

	new_channels.params = priv->channels.params;
	return mlx5e_safe_switch_channels(priv, &new_channels, NULL);
}