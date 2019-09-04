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
typedef  int /*<<< orphan*/  u64 ;
struct uverbs_attr_bundle {int dummy; } ;
struct ib_flow_action {int dummy; } ;
struct TYPE_10__ {int ib_flags; int /*<<< orphan*/  ctx; } ;
struct mlx5_ib_flow_action {struct ib_flow_action ib_action; TYPE_5__ esp_aes_gcm; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct TYPE_8__ {int key_len; int icv_len; int /*<<< orphan*/  iv_algo; int /*<<< orphan*/  seq_iv; int /*<<< orphan*/  salt; int /*<<< orphan*/  aes_key; } ;
struct TYPE_9__ {TYPE_3__ aes_gcm; } ;
struct mlx5_accel_esp_xfrm_attrs {int /*<<< orphan*/  action; int /*<<< orphan*/  flags; int /*<<< orphan*/  esn; int /*<<< orphan*/  keymat_type; TYPE_4__ keymat; } ;
struct ib_uverbs_flow_action_esp_keymat_aes_gcm {int icv_len; scalar_t__ iv_algo; int key_len; int /*<<< orphan*/  iv; int /*<<< orphan*/  salt; int /*<<< orphan*/  aes_key; } ;
struct ib_flow_action_attrs_esp {int flags; int /*<<< orphan*/  esn; TYPE_2__* keymat; scalar_t__ hard_limit_pkts; scalar_t__ tfc_pad; scalar_t__ seq; scalar_t__ spi; scalar_t__ encap; scalar_t__ replay; } ;
struct ib_device {int dummy; } ;
struct TYPE_6__ {struct ib_uverbs_flow_action_esp_keymat_aes_gcm aes_gcm; } ;
struct TYPE_7__ {scalar_t__ protocol; TYPE_1__ keymat; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 struct ib_flow_action* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED ; 
 int IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ENCRYPT ; 
 int IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ESN_NEW_WINDOW ; 
 scalar_t__ IB_UVERBS_FLOW_ACTION_ESP_KEYMAT_AES_GCM ; 
 scalar_t__ IB_UVERBS_FLOW_ACTION_IV_ALGO_SEQ ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_ACCEL_ESP_ACTION_ENCRYPT ; 
 int /*<<< orphan*/  MLX5_ACCEL_ESP_AES_GCM_IV_ALGO_SEQ ; 
 int /*<<< orphan*/  MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP ; 
 int /*<<< orphan*/  MLX5_ACCEL_ESP_FLAGS_ESN_TRIGGERED ; 
 int /*<<< orphan*/  MLX5_ACCEL_ESP_KEYMAT_AES_GCM ; 
 int MLX5_FLOW_ACTION_ESP_CREATE_LAST_SUPPORTED ; 
 int /*<<< orphan*/  MLX5_IB_ATTR_CREATE_FLOW_ACTION_FLAGS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_flow_action*) ; 
 struct mlx5_ib_flow_action* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5_accel_esp_create_xfrm (int /*<<< orphan*/ ,struct mlx5_accel_esp_xfrm_attrs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_flow_action_flags_to_accel_xfrm_flags (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* to_mdev (struct ib_device*) ; 
 int uverbs_get_flags64 (int /*<<< orphan*/ *,struct uverbs_attr_bundle*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ib_flow_action *
mlx5_ib_create_flow_action_esp(struct ib_device *device,
			       const struct ib_flow_action_attrs_esp *attr,
			       struct uverbs_attr_bundle *attrs)
{
	struct mlx5_ib_dev *mdev = to_mdev(device);
	struct ib_uverbs_flow_action_esp_keymat_aes_gcm *aes_gcm;
	struct mlx5_accel_esp_xfrm_attrs accel_attrs = {};
	struct mlx5_ib_flow_action *action;
	u64 action_flags;
	u64 flags;
	int err = 0;

	err = uverbs_get_flags64(
		&action_flags, attrs, MLX5_IB_ATTR_CREATE_FLOW_ACTION_FLAGS,
		((MLX5_FLOW_ACTION_ESP_CREATE_LAST_SUPPORTED << 1) - 1));
	if (err)
		return ERR_PTR(err);

	flags = mlx5_ib_flow_action_flags_to_accel_xfrm_flags(action_flags);

	/* We current only support a subset of the standard features. Only a
	 * keymat of type AES_GCM, with icv_len == 16, iv_algo == SEQ and esn
	 * (with overlap). Full offload mode isn't supported.
	 */
	if (!attr->keymat || attr->replay || attr->encap ||
	    attr->spi || attr->seq || attr->tfc_pad ||
	    attr->hard_limit_pkts ||
	    (attr->flags & ~(IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED |
			     IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ENCRYPT)))
		return ERR_PTR(-EOPNOTSUPP);

	if (attr->keymat->protocol !=
	    IB_UVERBS_FLOW_ACTION_ESP_KEYMAT_AES_GCM)
		return ERR_PTR(-EOPNOTSUPP);

	aes_gcm = &attr->keymat->keymat.aes_gcm;

	if (aes_gcm->icv_len != 16 ||
	    aes_gcm->iv_algo != IB_UVERBS_FLOW_ACTION_IV_ALGO_SEQ)
		return ERR_PTR(-EOPNOTSUPP);

	action = kmalloc(sizeof(*action), GFP_KERNEL);
	if (!action)
		return ERR_PTR(-ENOMEM);

	action->esp_aes_gcm.ib_flags = attr->flags;
	memcpy(&accel_attrs.keymat.aes_gcm.aes_key, &aes_gcm->aes_key,
	       sizeof(accel_attrs.keymat.aes_gcm.aes_key));
	accel_attrs.keymat.aes_gcm.key_len = aes_gcm->key_len * 8;
	memcpy(&accel_attrs.keymat.aes_gcm.salt, &aes_gcm->salt,
	       sizeof(accel_attrs.keymat.aes_gcm.salt));
	memcpy(&accel_attrs.keymat.aes_gcm.seq_iv, &aes_gcm->iv,
	       sizeof(accel_attrs.keymat.aes_gcm.seq_iv));
	accel_attrs.keymat.aes_gcm.icv_len = aes_gcm->icv_len * 8;
	accel_attrs.keymat.aes_gcm.iv_algo = MLX5_ACCEL_ESP_AES_GCM_IV_ALGO_SEQ;
	accel_attrs.keymat_type = MLX5_ACCEL_ESP_KEYMAT_AES_GCM;

	accel_attrs.esn = attr->esn;
	if (attr->flags & IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED)
		accel_attrs.flags |= MLX5_ACCEL_ESP_FLAGS_ESN_TRIGGERED;
	if (attr->flags & IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ESN_NEW_WINDOW)
		accel_attrs.flags |= MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP;

	if (attr->flags & IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ENCRYPT)
		accel_attrs.action |= MLX5_ACCEL_ESP_ACTION_ENCRYPT;

	action->esp_aes_gcm.ctx =
		mlx5_accel_esp_create_xfrm(mdev->mdev, &accel_attrs, flags);
	if (IS_ERR(action->esp_aes_gcm.ctx)) {
		err = PTR_ERR(action->esp_aes_gcm.ctx);
		goto err_parse;
	}

	action->esp_aes_gcm.ib_flags = attr->flags;

	return &action->ib_action;

err_parse:
	kfree(action);
	return ERR_PTR(err);
}