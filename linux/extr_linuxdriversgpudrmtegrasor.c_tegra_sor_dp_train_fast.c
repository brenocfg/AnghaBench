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
typedef  int u8 ;
typedef  int u32 ;
struct tegra_sor {int /*<<< orphan*/  aux; TYPE_2__* soc; } ;
struct drm_dp_link {unsigned int num_lanes; } ;
struct TYPE_4__ {TYPE_1__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  dp_padctl0; } ;

/* Variables and functions */
 int DP_LINK_SCRAMBLING_DISABLE ; 
 int /*<<< orphan*/  DP_SET_ANSI_8B10B ; 
 int DP_TRAINING_PATTERN_1 ; 
 int DP_TRAINING_PATTERN_2 ; 
 int DP_TRAINING_PATTERN_DISABLE ; 
 int SOR_DP_PADCTL_CM_TXD_0 ; 
 int SOR_DP_PADCTL_CM_TXD_1 ; 
 int SOR_DP_PADCTL_CM_TXD_2 ; 
 int SOR_DP_PADCTL_CM_TXD_3 ; 
 int SOR_DP_PADCTL_TX_PU (int) ; 
 int SOR_DP_PADCTL_TX_PU_ENABLE ; 
 int SOR_DP_PADCTL_TX_PU_MASK ; 
 int /*<<< orphan*/  SOR_DP_SPARE0 ; 
 int SOR_DP_SPARE_MACRO_SOR_CLK ; 
 int SOR_DP_SPARE_PANEL_INTERNAL ; 
 int SOR_DP_SPARE_SEQ_ENABLE ; 
 int /*<<< orphan*/  SOR_DP_TPG ; 
 unsigned long SOR_DP_TPG_CHANNEL_CODING ; 
 unsigned long SOR_DP_TPG_PATTERN_NONE ; 
 unsigned long SOR_DP_TPG_PATTERN_TRAIN1 ; 
 unsigned long SOR_DP_TPG_PATTERN_TRAIN2 ; 
 unsigned long SOR_DP_TPG_SCRAMBLER_GALIOS ; 
 unsigned long SOR_DP_TPG_SCRAMBLER_NONE ; 
 int /*<<< orphan*/  SOR_LANE_DRIVE_CURRENT0 ; 
 int SOR_LANE_DRIVE_CURRENT_LANE0 (int) ; 
 int SOR_LANE_DRIVE_CURRENT_LANE1 (int) ; 
 int SOR_LANE_DRIVE_CURRENT_LANE2 (int) ; 
 int SOR_LANE_DRIVE_CURRENT_LANE3 (int) ; 
 int /*<<< orphan*/  SOR_LANE_POSTCURSOR0 ; 
 int SOR_LANE_POSTCURSOR_LANE0 (int) ; 
 int SOR_LANE_POSTCURSOR_LANE1 (int) ; 
 int SOR_LANE_POSTCURSOR_LANE2 (int) ; 
 int SOR_LANE_POSTCURSOR_LANE3 (int) ; 
 int /*<<< orphan*/  SOR_LANE_PREEMPHASIS0 ; 
 int SOR_LANE_PREEMPHASIS_LANE0 (int) ; 
 int SOR_LANE_PREEMPHASIS_LANE1 (int) ; 
 int SOR_LANE_PREEMPHASIS_LANE2 (int) ; 
 int SOR_LANE_PREEMPHASIS_LANE3 (int) ; 
 int /*<<< orphan*/  SOR_LVDS ; 
 int drm_dp_aux_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_dp_aux_train (int /*<<< orphan*/ ,struct drm_dp_link*,int) ; 
 int tegra_sor_readl (struct tegra_sor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_sor_writel (struct tegra_sor*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tegra_sor_dp_train_fast(struct tegra_sor *sor,
				   struct drm_dp_link *link)
{
	unsigned int i;
	u8 pattern;
	u32 value;
	int err;

	/* setup lane parameters */
	value = SOR_LANE_DRIVE_CURRENT_LANE3(0x40) |
		SOR_LANE_DRIVE_CURRENT_LANE2(0x40) |
		SOR_LANE_DRIVE_CURRENT_LANE1(0x40) |
		SOR_LANE_DRIVE_CURRENT_LANE0(0x40);
	tegra_sor_writel(sor, value, SOR_LANE_DRIVE_CURRENT0);

	value = SOR_LANE_PREEMPHASIS_LANE3(0x0f) |
		SOR_LANE_PREEMPHASIS_LANE2(0x0f) |
		SOR_LANE_PREEMPHASIS_LANE1(0x0f) |
		SOR_LANE_PREEMPHASIS_LANE0(0x0f);
	tegra_sor_writel(sor, value, SOR_LANE_PREEMPHASIS0);

	value = SOR_LANE_POSTCURSOR_LANE3(0x00) |
		SOR_LANE_POSTCURSOR_LANE2(0x00) |
		SOR_LANE_POSTCURSOR_LANE1(0x00) |
		SOR_LANE_POSTCURSOR_LANE0(0x00);
	tegra_sor_writel(sor, value, SOR_LANE_POSTCURSOR0);

	/* disable LVDS mode */
	tegra_sor_writel(sor, 0, SOR_LVDS);

	value = tegra_sor_readl(sor, sor->soc->regs->dp_padctl0);
	value |= SOR_DP_PADCTL_TX_PU_ENABLE;
	value &= ~SOR_DP_PADCTL_TX_PU_MASK;
	value |= SOR_DP_PADCTL_TX_PU(2); /* XXX: don't hardcode? */
	tegra_sor_writel(sor, value, sor->soc->regs->dp_padctl0);

	value = tegra_sor_readl(sor, sor->soc->regs->dp_padctl0);
	value |= SOR_DP_PADCTL_CM_TXD_3 | SOR_DP_PADCTL_CM_TXD_2 |
		 SOR_DP_PADCTL_CM_TXD_1 | SOR_DP_PADCTL_CM_TXD_0;
	tegra_sor_writel(sor, value, sor->soc->regs->dp_padctl0);

	usleep_range(10, 100);

	value = tegra_sor_readl(sor, sor->soc->regs->dp_padctl0);
	value &= ~(SOR_DP_PADCTL_CM_TXD_3 | SOR_DP_PADCTL_CM_TXD_2 |
		   SOR_DP_PADCTL_CM_TXD_1 | SOR_DP_PADCTL_CM_TXD_0);
	tegra_sor_writel(sor, value, sor->soc->regs->dp_padctl0);

	err = drm_dp_aux_prepare(sor->aux, DP_SET_ANSI_8B10B);
	if (err < 0)
		return err;

	for (i = 0, value = 0; i < link->num_lanes; i++) {
		unsigned long lane = SOR_DP_TPG_CHANNEL_CODING |
				     SOR_DP_TPG_SCRAMBLER_NONE |
				     SOR_DP_TPG_PATTERN_TRAIN1;
		value = (value << 8) | lane;
	}

	tegra_sor_writel(sor, value, SOR_DP_TPG);

	pattern = DP_TRAINING_PATTERN_1;

	err = drm_dp_aux_train(sor->aux, link, pattern);
	if (err < 0)
		return err;

	value = tegra_sor_readl(sor, SOR_DP_SPARE0);
	value |= SOR_DP_SPARE_SEQ_ENABLE;
	value &= ~SOR_DP_SPARE_PANEL_INTERNAL;
	value |= SOR_DP_SPARE_MACRO_SOR_CLK;
	tegra_sor_writel(sor, value, SOR_DP_SPARE0);

	for (i = 0, value = 0; i < link->num_lanes; i++) {
		unsigned long lane = SOR_DP_TPG_CHANNEL_CODING |
				     SOR_DP_TPG_SCRAMBLER_NONE |
				     SOR_DP_TPG_PATTERN_TRAIN2;
		value = (value << 8) | lane;
	}

	tegra_sor_writel(sor, value, SOR_DP_TPG);

	pattern = DP_LINK_SCRAMBLING_DISABLE | DP_TRAINING_PATTERN_2;

	err = drm_dp_aux_train(sor->aux, link, pattern);
	if (err < 0)
		return err;

	for (i = 0, value = 0; i < link->num_lanes; i++) {
		unsigned long lane = SOR_DP_TPG_CHANNEL_CODING |
				     SOR_DP_TPG_SCRAMBLER_GALIOS |
				     SOR_DP_TPG_PATTERN_NONE;
		value = (value << 8) | lane;
	}

	tegra_sor_writel(sor, value, SOR_DP_TPG);

	pattern = DP_TRAINING_PATTERN_DISABLE;

	err = drm_dp_aux_train(sor->aux, link, pattern);
	if (err < 0)
		return err;

	return 0;
}