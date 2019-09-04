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
struct msm_kms {int dummy; } ;
struct msm_drm_private {scalar_t__* dsi; } ;
struct msm_display_info {int* h_tile_instance; size_t num_of_h_tiles; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  intf_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct drm_encoder {TYPE_1__ base; TYPE_2__* dev; int /*<<< orphan*/  encoder_type; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_4__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MSM_DISPLAY_CAP_CMD_MODE ; 
 int /*<<< orphan*/  MSM_DISPLAY_CAP_VID_MODE ; 
 int dpu_encoder_setup (TYPE_2__*,struct drm_encoder*,struct msm_display_info*) ; 
 int /*<<< orphan*/  memset (struct msm_display_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _dpu_kms_set_encoder_mode(struct msm_kms *kms,
				 struct drm_encoder *encoder,
				 bool cmd_mode)
{
	struct msm_display_info info;
	struct msm_drm_private *priv = encoder->dev->dev_private;
	int i, rc = 0;

	memset(&info, 0, sizeof(info));

	info.intf_type = encoder->encoder_type;
	info.capabilities = cmd_mode ? MSM_DISPLAY_CAP_CMD_MODE :
			MSM_DISPLAY_CAP_VID_MODE;

	/* TODO: No support for DSI swap */
	for (i = 0; i < ARRAY_SIZE(priv->dsi); i++) {
		if (priv->dsi[i]) {
			info.h_tile_instance[info.num_of_h_tiles] = i;
			info.num_of_h_tiles++;
		}
	}

	rc = dpu_encoder_setup(encoder->dev, encoder, &info);
	if (rc)
		DPU_ERROR("failed to setup DPU encoder %d: rc:%d\n",
			encoder->base.id, rc);
}