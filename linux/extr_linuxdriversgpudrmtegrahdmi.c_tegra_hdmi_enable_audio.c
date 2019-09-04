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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENERIC_CTRL_AUDIO ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_HDMI_GENERIC_CTRL ; 
 int /*<<< orphan*/  tegra_hdmi_readl (struct tegra_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_hdmi_writel (struct tegra_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_hdmi_enable_audio(struct tegra_hdmi *hdmi)
{
	u32 value;

	value = tegra_hdmi_readl(hdmi, HDMI_NV_PDISP_HDMI_GENERIC_CTRL);
	value |= GENERIC_CTRL_AUDIO;
	tegra_hdmi_writel(hdmi, value, HDMI_NV_PDISP_HDMI_GENERIC_CTRL);
}