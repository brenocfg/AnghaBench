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
 int mlx5e_reporter_rx_create (struct mlx5e_priv*) ; 
 int mlx5e_reporter_tx_create (struct mlx5e_priv*) ; 

int mlx5e_health_create_reporters(struct mlx5e_priv *priv)
{
	int err;

	err = mlx5e_reporter_tx_create(priv);
	if (err)
		return err;

	err = mlx5e_reporter_rx_create(priv);
	if (err)
		return err;

	return 0;
}