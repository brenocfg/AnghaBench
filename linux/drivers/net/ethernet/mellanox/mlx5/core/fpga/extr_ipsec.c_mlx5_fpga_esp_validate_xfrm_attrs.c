#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx5_core_dev {TYPE_4__* fpga; } ;
struct TYPE_5__ {scalar_t__ iv_algo; int icv_len; int key_len; } ;
struct TYPE_6__ {TYPE_1__ aes_gcm; } ;
struct mlx5_accel_esp_xfrm_attrs {scalar_t__ replay_type; scalar_t__ keymat_type; int flags; TYPE_2__ keymat; scalar_t__ tfc_pad; } ;
struct TYPE_8__ {TYPE_3__* ipsec; } ;
struct TYPE_7__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ MLX5_ACCEL_ESP_AES_GCM_IV_ALGO_SEQ ; 
 int MLX5_ACCEL_ESP_FLAGS_ESN_TRIGGERED ; 
 scalar_t__ MLX5_ACCEL_ESP_KEYMAT_AES_GCM ; 
 scalar_t__ MLX5_ACCEL_ESP_REPLAY_NONE ; 
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipsec_extended_cap ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  v2_command ; 

__attribute__((used)) static int
mlx5_fpga_esp_validate_xfrm_attrs(struct mlx5_core_dev *mdev,
				  const struct mlx5_accel_esp_xfrm_attrs *attrs)
{
	if (attrs->tfc_pad) {
		mlx5_core_err(mdev, "Cannot offload xfrm states with tfc padding\n");
		return -EOPNOTSUPP;
	}

	if (attrs->replay_type != MLX5_ACCEL_ESP_REPLAY_NONE) {
		mlx5_core_err(mdev, "Cannot offload xfrm states with anti replay\n");
		return -EOPNOTSUPP;
	}

	if (attrs->keymat_type != MLX5_ACCEL_ESP_KEYMAT_AES_GCM) {
		mlx5_core_err(mdev, "Only aes gcm keymat is supported\n");
		return -EOPNOTSUPP;
	}

	if (attrs->keymat.aes_gcm.iv_algo !=
	    MLX5_ACCEL_ESP_AES_GCM_IV_ALGO_SEQ) {
		mlx5_core_err(mdev, "Only iv sequence algo is supported\n");
		return -EOPNOTSUPP;
	}

	if (attrs->keymat.aes_gcm.icv_len != 128) {
		mlx5_core_err(mdev, "Cannot offload xfrm states with AEAD ICV length other than 128bit\n");
		return -EOPNOTSUPP;
	}

	if (attrs->keymat.aes_gcm.key_len != 128 &&
	    attrs->keymat.aes_gcm.key_len != 256) {
		mlx5_core_err(mdev, "Cannot offload xfrm states with AEAD key length other than 128/256 bit\n");
		return -EOPNOTSUPP;
	}

	if ((attrs->flags & MLX5_ACCEL_ESP_FLAGS_ESN_TRIGGERED) &&
	    (!MLX5_GET(ipsec_extended_cap, mdev->fpga->ipsec->caps,
		       v2_command))) {
		mlx5_core_err(mdev, "Cannot offload xfrm states with AEAD key length other than 128/256 bit\n");
		return -EOPNOTSUPP;
	}

	return 0;
}