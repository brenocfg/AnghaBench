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
struct cdn_dp_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  spdif_rst; } ;
struct audio_info {scalar_t__ format; } ;

/* Variables and functions */
 scalar_t__ AFMT_I2S ; 
 scalar_t__ AFMT_SPDIF ; 
 int /*<<< orphan*/  AUDIO_PACK_CONTROL ; 
 int /*<<< orphan*/  AUDIO_PACK_EN ; 
 int /*<<< orphan*/  CM_CTRL ; 
 int /*<<< orphan*/  CM_LANE_CTRL ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  LANE_REF_CYC ; 
 int /*<<< orphan*/  cdn_dp_audio_config_i2s (struct cdn_dp_device*,struct audio_info*) ; 
 int /*<<< orphan*/  cdn_dp_audio_config_spdif (struct cdn_dp_device*) ; 
 int cdn_dp_reg_write (struct cdn_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 

int cdn_dp_audio_config(struct cdn_dp_device *dp, struct audio_info *audio)
{
	int ret;

	/* reset the spdif clk before config */
	if (audio->format == AFMT_SPDIF) {
		reset_control_assert(dp->spdif_rst);
		reset_control_deassert(dp->spdif_rst);
	}

	ret = cdn_dp_reg_write(dp, CM_LANE_CTRL, LANE_REF_CYC);
	if (ret)
		goto err_audio_config;

	ret = cdn_dp_reg_write(dp, CM_CTRL, 0);
	if (ret)
		goto err_audio_config;

	if (audio->format == AFMT_I2S)
		cdn_dp_audio_config_i2s(dp, audio);
	else if (audio->format == AFMT_SPDIF)
		cdn_dp_audio_config_spdif(dp);

	ret = cdn_dp_reg_write(dp, AUDIO_PACK_CONTROL, AUDIO_PACK_EN);

err_audio_config:
	if (ret)
		DRM_DEV_ERROR(dp->dev, "audio config failed: %d\n", ret);
	return ret;
}