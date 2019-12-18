#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct TYPE_4__ {int /*<<< orphan*/  rqn; } ;
struct mlx5e_redirect_rqt_param {int is_rss; TYPE_1__ member_1; } ;
struct mlx5e_priv {TYPE_3__* xsk_tir; } ;
struct TYPE_5__ {int /*<<< orphan*/  rqtn; } ;
struct TYPE_6__ {TYPE_2__ rqt; } ;

/* Variables and functions */
 int mlx5e_redirect_rqt (struct mlx5e_priv*,int /*<<< orphan*/ ,int,struct mlx5e_redirect_rqt_param) ; 

__attribute__((used)) static int mlx5e_redirect_xsk_rqt(struct mlx5e_priv *priv, u16 ix, u32 rqn)
{
	struct mlx5e_redirect_rqt_param direct_rrp = {
		.is_rss = false,
		{
			.rqn = rqn,
		},
	};

	u32 rqtn = priv->xsk_tir[ix].rqt.rqtn;

	return mlx5e_redirect_rqt(priv, rqtn, 1, direct_rrp);
}