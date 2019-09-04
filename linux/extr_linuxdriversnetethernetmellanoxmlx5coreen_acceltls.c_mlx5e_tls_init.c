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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlx5e_tls* kzalloc (int,int /*<<< orphan*/ ) ; 

int mlx5e_tls_init(struct mlx5e_priv *priv)
{
	struct mlx5e_tls *tls = kzalloc(sizeof(*tls), GFP_KERNEL);

	if (!tls)
		return -ENOMEM;

	priv->tls = tls;
	return 0;
}