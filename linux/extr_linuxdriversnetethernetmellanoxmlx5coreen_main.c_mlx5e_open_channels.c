#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5e_priv {int dummy; } ;
struct TYPE_3__ {int num_channels; } ;
struct mlx5e_channels {int num; int /*<<< orphan*/ * c; TYPE_1__ params; } ;
struct mlx5e_channel_param {int dummy; } ;
struct mlx5e_channel {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvfree (struct mlx5e_channel_param*) ; 
 struct mlx5e_channel_param* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_build_channel_param (struct mlx5e_priv*,TYPE_1__*,struct mlx5e_channel_param*) ; 
 int /*<<< orphan*/  mlx5e_close_channel (int /*<<< orphan*/ ) ; 
 int mlx5e_open_channel (struct mlx5e_priv*,int,TYPE_1__*,struct mlx5e_channel_param*,int /*<<< orphan*/ *) ; 

int mlx5e_open_channels(struct mlx5e_priv *priv,
			struct mlx5e_channels *chs)
{
	struct mlx5e_channel_param *cparam;
	int err = -ENOMEM;
	int i;

	chs->num = chs->params.num_channels;

	chs->c = kcalloc(chs->num, sizeof(struct mlx5e_channel *), GFP_KERNEL);
	cparam = kvzalloc(sizeof(struct mlx5e_channel_param), GFP_KERNEL);
	if (!chs->c || !cparam)
		goto err_free;

	mlx5e_build_channel_param(priv, &chs->params, cparam);
	for (i = 0; i < chs->num; i++) {
		err = mlx5e_open_channel(priv, i, &chs->params, cparam, &chs->c[i]);
		if (err)
			goto err_close_channels;
	}

	kvfree(cparam);
	return 0;

err_close_channels:
	for (i--; i >= 0; i--)
		mlx5e_close_channel(chs->c[i]);

err_free:
	kfree(chs->c);
	kvfree(cparam);
	chs->num = 0;
	return err;
}