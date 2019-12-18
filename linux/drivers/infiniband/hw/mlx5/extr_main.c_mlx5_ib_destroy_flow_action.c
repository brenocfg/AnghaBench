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
struct TYPE_2__ {int /*<<< orphan*/  ctx; } ;
struct mlx5_ib_flow_action {TYPE_1__ esp_aes_gcm; } ;
struct ib_flow_action {int type; } ;

/* Variables and functions */
#define  IB_FLOW_ACTION_ESP 129 
#define  IB_FLOW_ACTION_UNSPECIFIED 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_flow_action*) ; 
 int /*<<< orphan*/  mlx5_accel_esp_destroy_xfrm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_destroy_flow_action_raw (struct mlx5_ib_flow_action*) ; 
 struct mlx5_ib_flow_action* to_mflow_act (struct ib_flow_action*) ; 

__attribute__((used)) static int mlx5_ib_destroy_flow_action(struct ib_flow_action *action)
{
	struct mlx5_ib_flow_action *maction = to_mflow_act(action);

	switch (action->type) {
	case IB_FLOW_ACTION_ESP:
		/*
		 * We only support aes_gcm by now, so we implicitly know this is
		 * the underline crypto.
		 */
		mlx5_accel_esp_destroy_xfrm(maction->esp_aes_gcm.ctx);
		break;
	case IB_FLOW_ACTION_UNSPECIFIED:
		mlx5_ib_destroy_flow_action_raw(maction);
		break;
	default:
		WARN_ON(true);
		break;
	}

	kfree(maction);
	return 0;
}