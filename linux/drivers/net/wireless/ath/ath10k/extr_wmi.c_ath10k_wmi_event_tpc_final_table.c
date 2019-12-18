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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wmi_pdev_tpc_final_table_event {int /*<<< orphan*/  rate_max; int /*<<< orphan*/  num_tx_chain; int /*<<< orphan*/  twice_max_rd_power; int /*<<< orphan*/  power_limit; int /*<<< orphan*/  twice_antenna_reduction; int /*<<< orphan*/  twice_antenna_gain; int /*<<< orphan*/  reg_domain; int /*<<< orphan*/  ctl; int /*<<< orphan*/  phy_mode; int /*<<< orphan*/  chan_freq; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k_tpc_stats_final {int chan_freq; int phy_mode; int ctl; int reg_domain; int twice_antenna_reduction; int power_limit; int twice_max_rd_power; int num_tx_chain; int rate_max; int /*<<< orphan*/  twice_antenna_gain; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int WMI_TPC_FINAL_RATE_MAX ; 
 int WMI_TPC_PREAM_TABLE_MAX ; 
 int /*<<< orphan*/  WMI_TPC_TABLE_TYPE_CDD ; 
 int /*<<< orphan*/  WMI_TPC_TABLE_TYPE_STBC ; 
 int /*<<< orphan*/  WMI_TPC_TABLE_TYPE_TXBF ; 
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a_sle32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  ath10k_debug_tpc_stats_final_process (struct ath10k*,struct ath10k_tpc_stats_final*) ; 
 int /*<<< orphan*/  ath10k_wmi_tpc_config_get_rate_code (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ath10k_wmi_tpc_stats_final_disp_tables (struct ath10k*,struct wmi_pdev_tpc_final_table_event*,struct ath10k_tpc_stats_final*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ath10k_tpc_stats_final* kzalloc (int,int /*<<< orphan*/ ) ; 

void ath10k_wmi_event_tpc_final_table(struct ath10k *ar, struct sk_buff *skb)
{
	u32 num_tx_chain;
	u8 rate_code[WMI_TPC_FINAL_RATE_MAX];
	u16 pream_table[WMI_TPC_PREAM_TABLE_MAX];
	struct wmi_pdev_tpc_final_table_event *ev;
	struct ath10k_tpc_stats_final *tpc_stats;

	ev = (struct wmi_pdev_tpc_final_table_event *)skb->data;

	tpc_stats = kzalloc(sizeof(*tpc_stats), GFP_ATOMIC);
	if (!tpc_stats)
		return;

	num_tx_chain = __le32_to_cpu(ev->num_tx_chain);

	ath10k_wmi_tpc_config_get_rate_code(rate_code, pream_table,
					    num_tx_chain);

	tpc_stats->chan_freq = __le32_to_cpu(ev->chan_freq);
	tpc_stats->phy_mode = __le32_to_cpu(ev->phy_mode);
	tpc_stats->ctl = __le32_to_cpu(ev->ctl);
	tpc_stats->reg_domain = __le32_to_cpu(ev->reg_domain);
	tpc_stats->twice_antenna_gain = a_sle32_to_cpu(ev->twice_antenna_gain);
	tpc_stats->twice_antenna_reduction =
		__le32_to_cpu(ev->twice_antenna_reduction);
	tpc_stats->power_limit = __le32_to_cpu(ev->power_limit);
	tpc_stats->twice_max_rd_power = __le32_to_cpu(ev->twice_max_rd_power);
	tpc_stats->num_tx_chain = __le32_to_cpu(ev->num_tx_chain);
	tpc_stats->rate_max = __le32_to_cpu(ev->rate_max);

	ath10k_wmi_tpc_stats_final_disp_tables(ar, ev, tpc_stats,
					       rate_code, pream_table,
					       WMI_TPC_TABLE_TYPE_CDD);
	ath10k_wmi_tpc_stats_final_disp_tables(ar, ev,  tpc_stats,
					       rate_code, pream_table,
					       WMI_TPC_TABLE_TYPE_STBC);
	ath10k_wmi_tpc_stats_final_disp_tables(ar, ev, tpc_stats,
					       rate_code, pream_table,
					       WMI_TPC_TABLE_TYPE_TXBF);

	ath10k_debug_tpc_stats_final_process(ar, tpc_stats);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi event tpc final table channel %d mode %d ctl %d regd %d gain %d %d limit %d max_power %d tx_chanins %d rates %d\n",
		   __le32_to_cpu(ev->chan_freq),
		   __le32_to_cpu(ev->phy_mode),
		   __le32_to_cpu(ev->ctl),
		   __le32_to_cpu(ev->reg_domain),
		   a_sle32_to_cpu(ev->twice_antenna_gain),
		   __le32_to_cpu(ev->twice_antenna_reduction),
		   __le32_to_cpu(ev->power_limit),
		   __le32_to_cpu(ev->twice_max_rd_power) / 2,
		   __le32_to_cpu(ev->num_tx_chain),
		   __le32_to_cpu(ev->rate_max));
}