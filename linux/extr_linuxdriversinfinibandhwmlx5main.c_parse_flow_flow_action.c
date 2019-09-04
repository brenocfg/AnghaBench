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
struct TYPE_4__ {int /*<<< orphan*/  act; } ;
union ib_flow_spec {TYPE_1__ action; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_5__ {int type; } ;
struct mlx5_ib_flow_action {TYPE_3__ esp_aes_gcm; TYPE_2__ ib_action; } ;
struct mlx5_flow_act {uintptr_t esp_id; int /*<<< orphan*/  action; } ;
struct ib_flow_attr {int flags; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  IB_FLOW_ACTION_ESP 128 
 int IB_FLOW_ATTR_FLAGS_EGRESS ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_DECRYPT ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_ENCRYPT ; 
 struct mlx5_ib_flow_action* to_mflow_act (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_flow_flow_action(const union ib_flow_spec *ib_spec,
				  const struct ib_flow_attr *flow_attr,
				  struct mlx5_flow_act *action)
{
	struct mlx5_ib_flow_action *maction = to_mflow_act(ib_spec->action.act);

	switch (maction->ib_action.type) {
	case IB_FLOW_ACTION_ESP:
		/* Currently only AES_GCM keymat is supported by the driver */
		action->esp_id = (uintptr_t)maction->esp_aes_gcm.ctx;
		action->action |= flow_attr->flags & IB_FLOW_ATTR_FLAGS_EGRESS ?
			MLX5_FLOW_CONTEXT_ACTION_ENCRYPT :
			MLX5_FLOW_CONTEXT_ACTION_DECRYPT;
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}