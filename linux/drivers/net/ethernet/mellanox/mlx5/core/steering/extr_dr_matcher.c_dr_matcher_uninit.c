#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5dr_matcher {int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; TYPE_1__* tbl; } ;
struct mlx5dr_domain {int type; } ;
struct TYPE_2__ {struct mlx5dr_domain* dmn; } ;

/* Variables and functions */
#define  MLX5DR_DOMAIN_TYPE_FDB 130 
#define  MLX5DR_DOMAIN_TYPE_NIC_RX 129 
#define  MLX5DR_DOMAIN_TYPE_NIC_TX 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dr_matcher_uninit_fdb (struct mlx5dr_matcher*) ; 
 int /*<<< orphan*/  dr_matcher_uninit_nic (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dr_matcher_uninit(struct mlx5dr_matcher *matcher)
{
	struct mlx5dr_domain *dmn = matcher->tbl->dmn;

	switch (dmn->type) {
	case MLX5DR_DOMAIN_TYPE_NIC_RX:
		dr_matcher_uninit_nic(&matcher->rx);
		break;
	case MLX5DR_DOMAIN_TYPE_NIC_TX:
		dr_matcher_uninit_nic(&matcher->tx);
		break;
	case MLX5DR_DOMAIN_TYPE_FDB:
		dr_matcher_uninit_fdb(matcher);
		break;
	default:
		WARN_ON(true);
		break;
	}
}