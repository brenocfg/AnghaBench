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
struct mlx5e_hairpin {int /*<<< orphan*/  indir_rqt; int /*<<< orphan*/  ttc; struct mlx5e_priv* func_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_destroy_rqt (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_destroy_ttc_table (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_hairpin_destroy_indirect_tirs (struct mlx5e_hairpin*) ; 

__attribute__((used)) static void mlx5e_hairpin_rss_cleanup(struct mlx5e_hairpin *hp)
{
	struct mlx5e_priv *priv = hp->func_priv;

	mlx5e_destroy_ttc_table(priv, &hp->ttc);
	mlx5e_hairpin_destroy_indirect_tirs(hp);
	mlx5e_destroy_rqt(priv, &hp->indir_rqt);
}