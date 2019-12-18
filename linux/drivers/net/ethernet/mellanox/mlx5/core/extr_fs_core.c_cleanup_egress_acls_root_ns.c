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
struct mlx5_flow_steering {int /*<<< orphan*/ * esw_egress_root_ns; } ;
struct TYPE_2__ {struct mlx5_flow_steering* steering; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_root_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int mlx5_eswitch_get_total_vports (struct mlx5_core_dev*) ; 

__attribute__((used)) static void cleanup_egress_acls_root_ns(struct mlx5_core_dev *dev)
{
	struct mlx5_flow_steering *steering = dev->priv.steering;
	int i;

	if (!steering->esw_egress_root_ns)
		return;

	for (i = 0; i < mlx5_eswitch_get_total_vports(dev); i++)
		cleanup_root_ns(steering->esw_egress_root_ns[i]);

	kfree(steering->esw_egress_root_ns);
	steering->esw_egress_root_ns = NULL;
}