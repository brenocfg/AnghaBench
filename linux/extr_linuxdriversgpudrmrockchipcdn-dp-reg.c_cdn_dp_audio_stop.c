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
struct cdn_dp_device {int /*<<< orphan*/  spdif_clk; scalar_t__ regs; int /*<<< orphan*/  dev; } ;
struct audio_info {scalar_t__ format; } ;

/* Variables and functions */
 scalar_t__ AFMT_SPDIF ; 
 int /*<<< orphan*/  AUDIO_PACK_CONTROL ; 
 scalar_t__ AUDIO_SRC_CNFG ; 
 scalar_t__ AUDIO_SRC_CNTL ; 
 int /*<<< orphan*/  AUDIO_SW_RST ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ FIFO_CNTL ; 
 scalar_t__ SMPL2PKT_CNTL ; 
 scalar_t__ SPDIF_CTRL_ADDR ; 
 int cdn_dp_reg_write (struct cdn_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int cdn_dp_audio_stop(struct cdn_dp_device *dp, struct audio_info *audio)
{
	int ret;

	ret = cdn_dp_reg_write(dp, AUDIO_PACK_CONTROL, 0);
	if (ret) {
		DRM_DEV_ERROR(dp->dev, "audio stop failed: %d\n", ret);
		return ret;
	}

	writel(0, dp->regs + SPDIF_CTRL_ADDR);

	/* clearn the audio config and reset */
	writel(0, dp->regs + AUDIO_SRC_CNTL);
	writel(0, dp->regs + AUDIO_SRC_CNFG);
	writel(AUDIO_SW_RST, dp->regs + AUDIO_SRC_CNTL);
	writel(0, dp->regs + AUDIO_SRC_CNTL);

	/* reset smpl2pckt component  */
	writel(0, dp->regs + SMPL2PKT_CNTL);
	writel(AUDIO_SW_RST, dp->regs + SMPL2PKT_CNTL);
	writel(0, dp->regs + SMPL2PKT_CNTL);

	/* reset FIFO */
	writel(AUDIO_SW_RST, dp->regs + FIFO_CNTL);
	writel(0, dp->regs + FIFO_CNTL);

	if (audio->format == AFMT_SPDIF)
		clk_disable_unprepare(dp->spdif_clk);

	return 0;
}