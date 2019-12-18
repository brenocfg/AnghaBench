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
struct mlx4_ib_qp {int /*<<< orphan*/  reg_id; int /*<<< orphan*/  ibqp; int /*<<< orphan*/  port; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;
struct ib_flow_spec_ib {int size; int /*<<< orphan*/  mask; int /*<<< orphan*/  type; } ;
struct ib_flow_attr {int num_of_specs; size_t size; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_FLOW_DOMAIN_NIC ; 
 int /*<<< orphan*/  IB_FLOW_SPEC_IB ; 
 int /*<<< orphan*/  MLX4_FS_REGULAR ; 
 int __mlx4_ib_create_flow (int /*<<< orphan*/ *,struct ib_flow_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int __mlx4_ib_destroy_flow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ib_flow_attr*) ; 
 struct ib_flow_attr* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int mlx4_ib_steer_qp_reg(struct mlx4_ib_dev *mdev, struct mlx4_ib_qp *mqp,
			 int is_attach)
{
	int err;
	size_t flow_size;
	struct ib_flow_attr *flow = NULL;
	struct ib_flow_spec_ib *ib_spec;

	if (is_attach) {
		flow_size = sizeof(struct ib_flow_attr) +
			    sizeof(struct ib_flow_spec_ib);
		flow = kzalloc(flow_size, GFP_KERNEL);
		if (!flow)
			return -ENOMEM;
		flow->port = mqp->port;
		flow->num_of_specs = 1;
		flow->size = flow_size;
		ib_spec = (struct ib_flow_spec_ib *)(flow + 1);
		ib_spec->type = IB_FLOW_SPEC_IB;
		ib_spec->size = sizeof(struct ib_flow_spec_ib);
		/* Add an empty rule for IB L2 */
		memset(&ib_spec->mask, 0, sizeof(ib_spec->mask));

		err = __mlx4_ib_create_flow(&mqp->ibqp, flow,
					    IB_FLOW_DOMAIN_NIC,
					    MLX4_FS_REGULAR,
					    &mqp->reg_id);
	} else {
		err = __mlx4_ib_destroy_flow(mdev->dev, mqp->reg_id);
	}
	kfree(flow);
	return err;
}