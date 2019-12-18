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
struct TYPE_3__ {int /*<<< orphan*/ * drop_counter; } ;
struct TYPE_4__ {int /*<<< orphan*/ * drop_counter; } ;
struct mlx5_vport {TYPE_1__ egress; int /*<<< orphan*/  vport; TYPE_2__ ingress; struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ MLX5_CAP_ESW_EGRESS_ACL (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_ESW_INGRESS_ACL (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_warn (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_counter ; 
 void* mlx5_fc_create (struct mlx5_core_dev*,int) ; 

__attribute__((used)) static void esw_vport_create_drop_counters(struct mlx5_vport *vport)
{
	struct mlx5_core_dev *dev = vport->dev;

	if (MLX5_CAP_ESW_INGRESS_ACL(dev, flow_counter)) {
		vport->ingress.drop_counter = mlx5_fc_create(dev, false);
		if (IS_ERR(vport->ingress.drop_counter)) {
			esw_warn(dev,
				 "vport[%d] configure ingress drop rule counter failed\n",
				 vport->vport);
			vport->ingress.drop_counter = NULL;
		}
	}

	if (MLX5_CAP_ESW_EGRESS_ACL(dev, flow_counter)) {
		vport->egress.drop_counter = mlx5_fc_create(dev, false);
		if (IS_ERR(vport->egress.drop_counter)) {
			esw_warn(dev,
				 "vport[%d] configure egress drop rule counter failed\n",
				 vport->vport);
			vport->egress.drop_counter = NULL;
		}
	}
}