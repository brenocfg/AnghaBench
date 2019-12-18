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
struct TYPE_2__ {int /*<<< orphan*/  channels; } ;
struct tegra_sor {int /*<<< orphan*/  dev; TYPE_1__ format; } ;
struct hdmi_audio_infoframe {int /*<<< orphan*/  channels; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO ; 
 int HDMI_INFOFRAME_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFOFRAME_CTRL_CHECKSUM_ENABLE ; 
 int /*<<< orphan*/  INFOFRAME_CTRL_ENABLE ; 
 int /*<<< orphan*/  SOR_HDMI_AUDIO_INFOFRAME_CTRL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int hdmi_audio_infoframe_init (struct hdmi_audio_infoframe*) ; 
 int hdmi_audio_infoframe_pack (struct hdmi_audio_infoframe*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tegra_sor_hdmi_write_infopack (struct tegra_sor*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tegra_sor_readl (struct tegra_sor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_sor_writel (struct tegra_sor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_sor_hdmi_enable_audio_infoframe(struct tegra_sor *sor)
{
	u8 buffer[HDMI_INFOFRAME_SIZE(AUDIO)];
	struct hdmi_audio_infoframe frame;
	u32 value;
	int err;

	err = hdmi_audio_infoframe_init(&frame);
	if (err < 0) {
		dev_err(sor->dev, "failed to setup audio infoframe: %d\n", err);
		return err;
	}

	frame.channels = sor->format.channels;

	err = hdmi_audio_infoframe_pack(&frame, buffer, sizeof(buffer));
	if (err < 0) {
		dev_err(sor->dev, "failed to pack audio infoframe: %d\n", err);
		return err;
	}

	tegra_sor_hdmi_write_infopack(sor, buffer, err);

	value = tegra_sor_readl(sor, SOR_HDMI_AUDIO_INFOFRAME_CTRL);
	value |= INFOFRAME_CTRL_CHECKSUM_ENABLE;
	value |= INFOFRAME_CTRL_ENABLE;
	tegra_sor_writel(sor, value, SOR_HDMI_AUDIO_INFOFRAME_CTRL);

	return 0;
}