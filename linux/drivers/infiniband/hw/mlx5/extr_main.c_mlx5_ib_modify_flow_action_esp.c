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
struct uverbs_attr_bundle {int dummy; } ;
struct TYPE_3__ {int ib_flags; TYPE_2__* ctx; } ;
struct mlx5_ib_flow_action {TYPE_1__ esp_aes_gcm; } ;
struct mlx5_accel_esp_xfrm_attrs {int /*<<< orphan*/  flags; int /*<<< orphan*/  esn; } ;
struct ib_flow_action_attrs_esp {int flags; int /*<<< orphan*/  esn; scalar_t__ hard_limit_pkts; scalar_t__ tfc_pad; scalar_t__ seq; scalar_t__ spi; scalar_t__ encap; scalar_t__ replay; scalar_t__ keymat; } ;
struct ib_flow_action {int dummy; } ;
typedef  int /*<<< orphan*/  accel_attrs ;
struct TYPE_4__ {int /*<<< orphan*/  attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED ; 
 int IB_FLOW_ACTION_ESP_FLAGS_MOD_ESP_ATTRS ; 
 int IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ESN_NEW_WINDOW ; 
 int /*<<< orphan*/  MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP ; 
 int /*<<< orphan*/  memcpy (struct mlx5_accel_esp_xfrm_attrs*,int /*<<< orphan*/ *,int) ; 
 int mlx5_accel_esp_modify_xfrm (TYPE_2__*,struct mlx5_accel_esp_xfrm_attrs*) ; 
 struct mlx5_ib_flow_action* to_mflow_act (struct ib_flow_action*) ; 

__attribute__((used)) static int
mlx5_ib_modify_flow_action_esp(struct ib_flow_action *action,
			       const struct ib_flow_action_attrs_esp *attr,
			       struct uverbs_attr_bundle *attrs)
{
	struct mlx5_ib_flow_action *maction = to_mflow_act(action);
	struct mlx5_accel_esp_xfrm_attrs accel_attrs;
	int err = 0;

	if (attr->keymat || attr->replay || attr->encap ||
	    attr->spi || attr->seq || attr->tfc_pad ||
	    attr->hard_limit_pkts ||
	    (attr->flags & ~(IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED |
			     IB_FLOW_ACTION_ESP_FLAGS_MOD_ESP_ATTRS |
			     IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ESN_NEW_WINDOW)))
		return -EOPNOTSUPP;

	/* Only the ESN value or the MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP can
	 * be modified.
	 */
	if (!(maction->esp_aes_gcm.ib_flags &
	      IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED) &&
	    attr->flags & (IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED |
			   IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ESN_NEW_WINDOW))
		return -EINVAL;

	memcpy(&accel_attrs, &maction->esp_aes_gcm.ctx->attrs,
	       sizeof(accel_attrs));

	accel_attrs.esn = attr->esn;
	if (attr->flags & IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ESN_NEW_WINDOW)
		accel_attrs.flags |= MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP;
	else
		accel_attrs.flags &= ~MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP;

	err = mlx5_accel_esp_modify_xfrm(maction->esp_aes_gcm.ctx,
					 &accel_attrs);
	if (err)
		return err;

	maction->esp_aes_gcm.ib_flags &=
		~IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ESN_NEW_WINDOW;
	maction->esp_aes_gcm.ib_flags |=
		attr->flags & IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ESN_NEW_WINDOW;

	return 0;
}