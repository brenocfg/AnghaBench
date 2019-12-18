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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  connector; } ;
struct tegra_sor {int /*<<< orphan*/  dev; TYPE_1__ output; } ;
struct hdmi_avi_infoframe {int dummy; } ;
struct drm_display_mode {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  AVI ; 
 int HDMI_INFOFRAME_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFOFRAME_CTRL_CHECKSUM_ENABLE ; 
 int /*<<< orphan*/  INFOFRAME_CTRL_ENABLE ; 
 int /*<<< orphan*/  INFOFRAME_CTRL_OTHER ; 
 int /*<<< orphan*/  INFOFRAME_CTRL_SINGLE ; 
 int /*<<< orphan*/  SOR_HDMI_AVI_INFOFRAME_CTRL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int drm_hdmi_avi_infoframe_from_display_mode (struct hdmi_avi_infoframe*,int /*<<< orphan*/ *,struct drm_display_mode const*) ; 
 int hdmi_avi_infoframe_pack (struct hdmi_avi_infoframe*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tegra_sor_hdmi_write_infopack (struct tegra_sor*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tegra_sor_readl (struct tegra_sor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_sor_writel (struct tegra_sor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_sor_hdmi_setup_avi_infoframe(struct tegra_sor *sor,
				   const struct drm_display_mode *mode)
{
	u8 buffer[HDMI_INFOFRAME_SIZE(AVI)];
	struct hdmi_avi_infoframe frame;
	u32 value;
	int err;

	/* disable AVI infoframe */
	value = tegra_sor_readl(sor, SOR_HDMI_AVI_INFOFRAME_CTRL);
	value &= ~INFOFRAME_CTRL_SINGLE;
	value &= ~INFOFRAME_CTRL_OTHER;
	value &= ~INFOFRAME_CTRL_ENABLE;
	tegra_sor_writel(sor, value, SOR_HDMI_AVI_INFOFRAME_CTRL);

	err = drm_hdmi_avi_infoframe_from_display_mode(&frame,
						       &sor->output.connector, mode);
	if (err < 0) {
		dev_err(sor->dev, "failed to setup AVI infoframe: %d\n", err);
		return err;
	}

	err = hdmi_avi_infoframe_pack(&frame, buffer, sizeof(buffer));
	if (err < 0) {
		dev_err(sor->dev, "failed to pack AVI infoframe: %d\n", err);
		return err;
	}

	tegra_sor_hdmi_write_infopack(sor, buffer, err);

	/* enable AVI infoframe */
	value = tegra_sor_readl(sor, SOR_HDMI_AVI_INFOFRAME_CTRL);
	value |= INFOFRAME_CTRL_CHECKSUM_ENABLE;
	value |= INFOFRAME_CTRL_ENABLE;
	tegra_sor_writel(sor, value, SOR_HDMI_AVI_INFOFRAME_CTRL);

	return 0;
}