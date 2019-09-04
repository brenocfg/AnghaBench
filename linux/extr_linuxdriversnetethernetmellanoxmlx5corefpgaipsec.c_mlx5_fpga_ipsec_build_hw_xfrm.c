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
struct TYPE_5__ {int /*<<< orphan*/ *** salt; int /*<<< orphan*/ *** salt_iv; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  enc_mode; void* sw_sa_handle; TYPE_2__ gcm; int /*<<< orphan*/ **** key_enc; } ;
struct mlx5_ifc_fpga_ipsec_sa {TYPE_3__ ipsec_sa_v1; void* esn; } ;
struct mlx5_core_dev {int dummy; } ;
struct aes_gcm_keymat {int key_len; int /*<<< orphan*/  salt; int /*<<< orphan*/  seq_iv; int /*<<< orphan*/ * aes_key; } ;
struct TYPE_4__ {struct aes_gcm_keymat aes_gcm; } ;
struct mlx5_accel_esp_xfrm_attrs {int flags; int action; int /*<<< orphan*/  sa_handle; int /*<<< orphan*/  esn; TYPE_1__ keymat; } ;

/* Variables and functions */
 int MLX5_ACCEL_ESP_ACTION_ENCRYPT ; 
 int MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP ; 
 int MLX5_ACCEL_ESP_FLAGS_ESN_TRIGGERED ; 
 int MLX5_FPGA_IPSEC_SA_DIR_SX ; 
 int /*<<< orphan*/  MLX5_FPGA_IPSEC_SA_ENC_MODE_AES_GCM_128_AUTH_128 ; 
 int /*<<< orphan*/  MLX5_FPGA_IPSEC_SA_ENC_MODE_AES_GCM_256_AUTH_128 ; 
 int MLX5_FPGA_IPSEC_SA_ESN_EN ; 
 int MLX5_FPGA_IPSEC_SA_ESN_OVERLAP ; 
 int MLX5_FPGA_IPSEC_SA_IP_ESP ; 
 int MLX5_FPGA_IPSEC_SA_SA_VALID ; 
 int MLX5_FPGA_IPSEC_SA_SPI_EN ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ***,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
mlx5_fpga_ipsec_build_hw_xfrm(struct mlx5_core_dev *mdev,
			      const struct mlx5_accel_esp_xfrm_attrs *xfrm_attrs,
			      struct mlx5_ifc_fpga_ipsec_sa *hw_sa)
{
	const struct aes_gcm_keymat *aes_gcm = &xfrm_attrs->keymat.aes_gcm;

	/* key */
	memcpy(&hw_sa->ipsec_sa_v1.key_enc, aes_gcm->aes_key,
	       aes_gcm->key_len / 8);
	/* Duplicate 128 bit key twice according to HW layout */
	if (aes_gcm->key_len == 128)
		memcpy(&hw_sa->ipsec_sa_v1.key_enc[16],
		       aes_gcm->aes_key, aes_gcm->key_len / 8);

	/* salt and seq_iv */
	memcpy(&hw_sa->ipsec_sa_v1.gcm.salt_iv, &aes_gcm->seq_iv,
	       sizeof(aes_gcm->seq_iv));
	memcpy(&hw_sa->ipsec_sa_v1.gcm.salt, &aes_gcm->salt,
	       sizeof(aes_gcm->salt));

	/* esn */
	if (xfrm_attrs->flags & MLX5_ACCEL_ESP_FLAGS_ESN_TRIGGERED) {
		hw_sa->ipsec_sa_v1.flags |= MLX5_FPGA_IPSEC_SA_ESN_EN;
		hw_sa->ipsec_sa_v1.flags |=
				(xfrm_attrs->flags &
				 MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP) ?
					MLX5_FPGA_IPSEC_SA_ESN_OVERLAP : 0;
		hw_sa->esn = htonl(xfrm_attrs->esn);
	} else {
		hw_sa->ipsec_sa_v1.flags &= ~MLX5_FPGA_IPSEC_SA_ESN_EN;
		hw_sa->ipsec_sa_v1.flags &=
				~(xfrm_attrs->flags &
				  MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP) ?
					MLX5_FPGA_IPSEC_SA_ESN_OVERLAP : 0;
		hw_sa->esn = 0;
	}

	/* rx handle */
	hw_sa->ipsec_sa_v1.sw_sa_handle = htonl(xfrm_attrs->sa_handle);

	/* enc mode */
	switch (aes_gcm->key_len) {
	case 128:
		hw_sa->ipsec_sa_v1.enc_mode =
			MLX5_FPGA_IPSEC_SA_ENC_MODE_AES_GCM_128_AUTH_128;
		break;
	case 256:
		hw_sa->ipsec_sa_v1.enc_mode =
			MLX5_FPGA_IPSEC_SA_ENC_MODE_AES_GCM_256_AUTH_128;
		break;
	}

	/* flags */
	hw_sa->ipsec_sa_v1.flags |= MLX5_FPGA_IPSEC_SA_SA_VALID |
			MLX5_FPGA_IPSEC_SA_SPI_EN |
			MLX5_FPGA_IPSEC_SA_IP_ESP;

	if (xfrm_attrs->action & MLX5_ACCEL_ESP_ACTION_ENCRYPT)
		hw_sa->ipsec_sa_v1.flags |= MLX5_FPGA_IPSEC_SA_DIR_SX;
	else
		hw_sa->ipsec_sa_v1.flags &= ~MLX5_FPGA_IPSEC_SA_DIR_SX;
}