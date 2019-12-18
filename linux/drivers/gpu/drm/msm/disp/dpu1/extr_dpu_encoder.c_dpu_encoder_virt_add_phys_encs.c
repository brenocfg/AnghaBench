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
typedef  int u32 ;
struct dpu_encoder_virt {int num_phys_encs; struct dpu_encoder_phys* cur_master; struct dpu_encoder_phys* cur_slave; struct dpu_encoder_phys** phys_encs; } ;
struct dpu_encoder_phys {int dummy; } ;
struct dpu_enc_phys_init_params {scalar_t__ split_role; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (struct dpu_encoder_phys**) ; 
 int /*<<< orphan*/  DPU_DEBUG_ENC (struct dpu_encoder_virt*,char*) ; 
 int /*<<< orphan*/  DPU_ERROR_ENC (struct dpu_encoder_virt*,char*,int) ; 
 int EINVAL ; 
 scalar_t__ ENC_ROLE_SLAVE ; 
 scalar_t__ IS_ERR_OR_NULL (struct dpu_encoder_phys*) ; 
 int MSM_DISPLAY_CAP_CMD_MODE ; 
 int MSM_DISPLAY_CAP_VID_MODE ; 
 scalar_t__ NUM_PHYS_ENCODER_TYPES ; 
 int PTR_ERR (struct dpu_encoder_phys*) ; 
 struct dpu_encoder_phys* dpu_encoder_phys_cmd_init (struct dpu_enc_phys_init_params*) ; 
 struct dpu_encoder_phys* dpu_encoder_phys_vid_init (struct dpu_enc_phys_init_params*) ; 

__attribute__((used)) static int dpu_encoder_virt_add_phys_encs(
		u32 display_caps,
		struct dpu_encoder_virt *dpu_enc,
		struct dpu_enc_phys_init_params *params)
{
	struct dpu_encoder_phys *enc = NULL;

	DPU_DEBUG_ENC(dpu_enc, "\n");

	/*
	 * We may create up to NUM_PHYS_ENCODER_TYPES physical encoder types
	 * in this function, check up-front.
	 */
	if (dpu_enc->num_phys_encs + NUM_PHYS_ENCODER_TYPES >=
			ARRAY_SIZE(dpu_enc->phys_encs)) {
		DPU_ERROR_ENC(dpu_enc, "too many physical encoders %d\n",
			  dpu_enc->num_phys_encs);
		return -EINVAL;
	}

	if (display_caps & MSM_DISPLAY_CAP_VID_MODE) {
		enc = dpu_encoder_phys_vid_init(params);

		if (IS_ERR_OR_NULL(enc)) {
			DPU_ERROR_ENC(dpu_enc, "failed to init vid enc: %ld\n",
				PTR_ERR(enc));
			return enc == 0 ? -EINVAL : PTR_ERR(enc);
		}

		dpu_enc->phys_encs[dpu_enc->num_phys_encs] = enc;
		++dpu_enc->num_phys_encs;
	}

	if (display_caps & MSM_DISPLAY_CAP_CMD_MODE) {
		enc = dpu_encoder_phys_cmd_init(params);

		if (IS_ERR_OR_NULL(enc)) {
			DPU_ERROR_ENC(dpu_enc, "failed to init cmd enc: %ld\n",
				PTR_ERR(enc));
			return enc == 0 ? -EINVAL : PTR_ERR(enc);
		}

		dpu_enc->phys_encs[dpu_enc->num_phys_encs] = enc;
		++dpu_enc->num_phys_encs;
	}

	if (params->split_role == ENC_ROLE_SLAVE)
		dpu_enc->cur_slave = enc;
	else
		dpu_enc->cur_master = enc;

	return 0;
}