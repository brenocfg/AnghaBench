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
struct tegra_sor_config {int hblank_symbols; int vblank_symbols; scalar_t__ active_polarity; int /*<<< orphan*/  active_frac; int /*<<< orphan*/  active_count; int /*<<< orphan*/  watermark; int /*<<< orphan*/  tu_size; } ;
struct tegra_sor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOR_DP_AUDIO_HBLANK_SYMBOLS ; 
 int SOR_DP_AUDIO_HBLANK_SYMBOLS_MASK ; 
 int /*<<< orphan*/  SOR_DP_AUDIO_VBLANK_SYMBOLS ; 
 int SOR_DP_AUDIO_VBLANK_SYMBOLS_MASK ; 
 int /*<<< orphan*/  SOR_DP_CONFIG0 ; 
 int SOR_DP_CONFIG_ACTIVE_SYM_COUNT (int /*<<< orphan*/ ) ; 
 int SOR_DP_CONFIG_ACTIVE_SYM_COUNT_MASK ; 
 int SOR_DP_CONFIG_ACTIVE_SYM_ENABLE ; 
 int SOR_DP_CONFIG_ACTIVE_SYM_FRAC (int /*<<< orphan*/ ) ; 
 int SOR_DP_CONFIG_ACTIVE_SYM_FRAC_MASK ; 
 int SOR_DP_CONFIG_ACTIVE_SYM_POLARITY ; 
 int SOR_DP_CONFIG_DISPARITY_NEGATIVE ; 
 int SOR_DP_CONFIG_WATERMARK (int /*<<< orphan*/ ) ; 
 int SOR_DP_CONFIG_WATERMARK_MASK ; 
 int /*<<< orphan*/  SOR_DP_LINKCTL0 ; 
 int SOR_DP_LINKCTL_TU_SIZE (int /*<<< orphan*/ ) ; 
 int SOR_DP_LINKCTL_TU_SIZE_MASK ; 
 int tegra_sor_readl (struct tegra_sor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_sor_writel (struct tegra_sor*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_sor_apply_config(struct tegra_sor *sor,
				   const struct tegra_sor_config *config)
{
	u32 value;

	value = tegra_sor_readl(sor, SOR_DP_LINKCTL0);
	value &= ~SOR_DP_LINKCTL_TU_SIZE_MASK;
	value |= SOR_DP_LINKCTL_TU_SIZE(config->tu_size);
	tegra_sor_writel(sor, value, SOR_DP_LINKCTL0);

	value = tegra_sor_readl(sor, SOR_DP_CONFIG0);
	value &= ~SOR_DP_CONFIG_WATERMARK_MASK;
	value |= SOR_DP_CONFIG_WATERMARK(config->watermark);

	value &= ~SOR_DP_CONFIG_ACTIVE_SYM_COUNT_MASK;
	value |= SOR_DP_CONFIG_ACTIVE_SYM_COUNT(config->active_count);

	value &= ~SOR_DP_CONFIG_ACTIVE_SYM_FRAC_MASK;
	value |= SOR_DP_CONFIG_ACTIVE_SYM_FRAC(config->active_frac);

	if (config->active_polarity)
		value |= SOR_DP_CONFIG_ACTIVE_SYM_POLARITY;
	else
		value &= ~SOR_DP_CONFIG_ACTIVE_SYM_POLARITY;

	value |= SOR_DP_CONFIG_ACTIVE_SYM_ENABLE;
	value |= SOR_DP_CONFIG_DISPARITY_NEGATIVE;
	tegra_sor_writel(sor, value, SOR_DP_CONFIG0);

	value = tegra_sor_readl(sor, SOR_DP_AUDIO_HBLANK_SYMBOLS);
	value &= ~SOR_DP_AUDIO_HBLANK_SYMBOLS_MASK;
	value |= config->hblank_symbols & 0xffff;
	tegra_sor_writel(sor, value, SOR_DP_AUDIO_HBLANK_SYMBOLS);

	value = tegra_sor_readl(sor, SOR_DP_AUDIO_VBLANK_SYMBOLS);
	value &= ~SOR_DP_AUDIO_VBLANK_SYMBOLS_MASK;
	value |= config->vblank_symbols & 0xffff;
	tegra_sor_writel(sor, value, SOR_DP_AUDIO_VBLANK_SYMBOLS);
}