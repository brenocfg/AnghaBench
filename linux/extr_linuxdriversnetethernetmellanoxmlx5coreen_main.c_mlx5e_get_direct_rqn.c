#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {TYPE_4__* channels; } ;
struct mlx5e_redirect_rqt_param {TYPE_5__ rss; int /*<<< orphan*/  rqn; int /*<<< orphan*/  is_rss; } ;
struct TYPE_6__ {int /*<<< orphan*/  rqn; } ;
struct mlx5e_priv {TYPE_1__ drop_rq; } ;
struct TYPE_9__ {int num; TYPE_3__** c; } ;
struct TYPE_7__ {int /*<<< orphan*/  rqn; } ;
struct TYPE_8__ {TYPE_2__ rq; } ;

/* Variables and functions */

__attribute__((used)) static u32 mlx5e_get_direct_rqn(struct mlx5e_priv *priv, int ix,
				struct mlx5e_redirect_rqt_param rrp)
{
	if (!rrp.is_rss)
		return rrp.rqn;

	if (ix >= rrp.rss.channels->num)
		return priv->drop_rq.rqn;

	return rrp.rss.channels->c[ix]->rq.rqn;
}