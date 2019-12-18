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
typedef  void* u64 ;
typedef  int u32 ;
struct survey_info {size_t noise; int filled; struct ieee80211_channel* channel; int /*<<< orphan*/  time; void* time_rx; void* time_busy; } ;
struct mwl8k_priv {TYPE_2__* hw; scalar_t__ channel_time; scalar_t__ regs; struct survey_info* survey; TYPE_1__* acs_chan; } ;
struct ieee80211_channel {int dummy; } ;
typedef  size_t s8 ;
struct TYPE_4__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_3__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBU_AVG_NOISE_VAL ; 
 scalar_t__ BBU_RXRDY_CNT_REG ; 
 size_t MWL8K_NUM_CHANS ; 
 scalar_t__ NOK_CCA_CNT_REG ; 
 int SURVEY_INFO_NOISE_DBM ; 
 int SURVEY_INFO_TIME ; 
 int SURVEY_INFO_TIME_BUSY ; 
 int SURVEY_INFO_TIME_RX ; 
 size_t freq_to_idx (struct mwl8k_priv*,int /*<<< orphan*/ ) ; 
 int ioread32 (scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  mwl8k_cmd_bbp_reg_access (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void mwl8k_update_survey(struct mwl8k_priv *priv,
				struct ieee80211_channel *channel)
{
	u32 cca_cnt, rx_rdy;
	s8 nf = 0, idx;
	struct survey_info *survey;

	idx = freq_to_idx(priv, priv->acs_chan->center_freq);
	if (idx >= MWL8K_NUM_CHANS) {
		wiphy_err(priv->hw->wiphy, "Failed to update survey\n");
		return;
	}

	survey = &priv->survey[idx];

	cca_cnt = ioread32(priv->regs + NOK_CCA_CNT_REG);
	cca_cnt /= 1000; /* uSecs to mSecs */
	survey->time_busy = (u64) cca_cnt;

	rx_rdy = ioread32(priv->regs + BBU_RXRDY_CNT_REG);
	rx_rdy /= 1000; /* uSecs to mSecs */
	survey->time_rx = (u64) rx_rdy;

	priv->channel_time = jiffies - priv->channel_time;
	survey->time = jiffies_to_msecs(priv->channel_time);

	survey->channel = channel;

	mwl8k_cmd_bbp_reg_access(priv->hw, 0, BBU_AVG_NOISE_VAL, &nf);

	/* Make sure sign is negative else ACS  at hostapd fails */
	survey->noise = nf * -1;

	survey->filled = SURVEY_INFO_NOISE_DBM |
			 SURVEY_INFO_TIME |
			 SURVEY_INFO_TIME_BUSY |
			 SURVEY_INFO_TIME_RX;
}