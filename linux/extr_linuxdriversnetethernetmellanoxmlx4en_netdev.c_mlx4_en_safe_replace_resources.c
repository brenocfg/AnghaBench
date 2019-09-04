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
struct mlx4_en_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_en_free_resources (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_update_priv (struct mlx4_en_priv*,struct mlx4_en_priv*) ; 

void mlx4_en_safe_replace_resources(struct mlx4_en_priv *priv,
				    struct mlx4_en_priv *tmp)
{
	mlx4_en_free_resources(priv);
	mlx4_en_update_priv(priv, tmp);
}