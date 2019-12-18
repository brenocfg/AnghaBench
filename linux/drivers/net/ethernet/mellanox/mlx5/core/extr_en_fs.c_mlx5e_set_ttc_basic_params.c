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
struct ttc_params {int /*<<< orphan*/ * inner_ttc; int /*<<< orphan*/  any_tt_tirn; } ;
struct TYPE_4__ {int /*<<< orphan*/  inner_ttc; } ;
struct mlx5e_priv {TYPE_2__ fs; TYPE_1__* direct_tir; } ;
struct TYPE_3__ {int /*<<< orphan*/  tirn; } ;

/* Variables and functions */

void mlx5e_set_ttc_basic_params(struct mlx5e_priv *priv,
				struct ttc_params *ttc_params)
{
	ttc_params->any_tt_tirn = priv->direct_tir[0].tirn;
	ttc_params->inner_ttc = &priv->fs.inner_ttc;
}