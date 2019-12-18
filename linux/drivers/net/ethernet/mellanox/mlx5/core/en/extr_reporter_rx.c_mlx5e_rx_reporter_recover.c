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
struct mlx5e_err_ctx {int dummy; } ;
struct devlink_health_reporter {int dummy; } ;

/* Variables and functions */
 struct mlx5e_priv* devlink_health_reporter_priv (struct devlink_health_reporter*) ; 
 int mlx5e_health_recover_channels (struct mlx5e_priv*) ; 
 int mlx5e_rx_reporter_recover_from_ctx (struct mlx5e_err_ctx*) ; 

__attribute__((used)) static int mlx5e_rx_reporter_recover(struct devlink_health_reporter *reporter,
				     void *context)
{
	struct mlx5e_priv *priv = devlink_health_reporter_priv(reporter);
	struct mlx5e_err_ctx *err_ctx = context;

	return err_ctx ? mlx5e_rx_reporter_recover_from_ctx(err_ctx) :
			 mlx5e_health_recover_channels(priv);
}