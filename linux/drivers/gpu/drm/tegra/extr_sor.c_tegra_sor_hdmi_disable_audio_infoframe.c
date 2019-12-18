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
struct tegra_sor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFOFRAME_CTRL_ENABLE ; 
 int /*<<< orphan*/  SOR_HDMI_AUDIO_INFOFRAME_CTRL ; 
 int /*<<< orphan*/  tegra_sor_readl (struct tegra_sor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_sor_writel (struct tegra_sor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_sor_hdmi_disable_audio_infoframe(struct tegra_sor *sor)
{
	u32 value;

	value = tegra_sor_readl(sor, SOR_HDMI_AUDIO_INFOFRAME_CTRL);
	value &= ~INFOFRAME_CTRL_ENABLE;
	tegra_sor_writel(sor, value, SOR_HDMI_AUDIO_INFOFRAME_CTRL);
}