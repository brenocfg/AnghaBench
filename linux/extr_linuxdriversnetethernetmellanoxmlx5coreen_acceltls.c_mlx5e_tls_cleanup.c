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
struct mlx5e_tls {int dummy; } ;
struct mlx5e_priv {struct mlx5e_tls* tls; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5e_tls*) ; 

void mlx5e_tls_cleanup(struct mlx5e_priv *priv)
{
	struct mlx5e_tls *tls = priv->tls;

	if (!tls)
		return;

	kfree(tls);
	priv->tls = NULL;
}