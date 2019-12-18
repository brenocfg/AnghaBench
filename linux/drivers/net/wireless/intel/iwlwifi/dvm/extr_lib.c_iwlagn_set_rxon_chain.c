#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_10__ {int /*<<< orphan*/  rx_chain; } ;
struct iwl_rxon_context {TYPE_5__ staging; } ;
struct TYPE_6__ {int active_chains; } ;
struct iwl_priv {scalar_t__ bt_traffic_load; scalar_t__ bt_full_concurrent; TYPE_4__* lib; TYPE_2__* nvm_data; TYPE_1__ chain_noise_data; int /*<<< orphan*/  status; } ;
struct TYPE_9__ {TYPE_3__* bt_params; } ;
struct TYPE_8__ {scalar_t__ advanced_bt_coexist; } ;
struct TYPE_7__ {int valid_rx_ant; } ;

/* Variables and functions */
 scalar_t__ IWL_BT_COEX_TRAFFIC_LOAD_HIGH ; 
 int /*<<< orphan*/  IWL_DEBUG_ASSOC (struct iwl_priv*,char*,int /*<<< orphan*/ ,int,int) ; 
 int IWL_NUM_RX_CHAINS_SINGLE ; 
 int RXON_RX_CHAIN_CNT_POS ; 
 int RXON_RX_CHAIN_MIMO_CNT_POS ; 
 int /*<<< orphan*/  RXON_RX_CHAIN_MIMO_FORCE_MSK ; 
 int RXON_RX_CHAIN_VALID_POS ; 
 int /*<<< orphan*/  STATUS_POWER_PMI ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int first_antenna (int) ; 
 int is_single_rx_stream (struct iwl_priv*) ; 
 int iwl_count_chain_bitmap (int) ; 
 int iwl_get_active_rx_chain_count (struct iwl_priv*) ; 
 int iwl_get_idle_rx_chain_count (struct iwl_priv*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void iwlagn_set_rxon_chain(struct iwl_priv *priv, struct iwl_rxon_context *ctx)
{
	bool is_single = is_single_rx_stream(priv);
	bool is_cam = !test_bit(STATUS_POWER_PMI, &priv->status);
	u8 idle_rx_cnt, active_rx_cnt, valid_rx_cnt;
	u32 active_chains;
	u16 rx_chain;

	/* Tell uCode which antennas are actually connected.
	 * Before first association, we assume all antennas are connected.
	 * Just after first association, iwl_chain_noise_calibration()
	 *    checks which antennas actually *are* connected. */
	if (priv->chain_noise_data.active_chains)
		active_chains = priv->chain_noise_data.active_chains;
	else
		active_chains = priv->nvm_data->valid_rx_ant;

	if (priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist &&
	    (priv->bt_full_concurrent ||
	     priv->bt_traffic_load >= IWL_BT_COEX_TRAFFIC_LOAD_HIGH)) {
		/*
		 * only use chain 'A' in bt high traffic load or
		 * full concurrency mode
		 */
		active_chains = first_antenna(active_chains);
	}

	rx_chain = active_chains << RXON_RX_CHAIN_VALID_POS;

	/* How many receivers should we use? */
	active_rx_cnt = iwl_get_active_rx_chain_count(priv);
	idle_rx_cnt = iwl_get_idle_rx_chain_count(priv, active_rx_cnt);


	/* correct rx chain count according hw settings
	 * and chain noise calibration
	 */
	valid_rx_cnt = iwl_count_chain_bitmap(active_chains);
	if (valid_rx_cnt < active_rx_cnt)
		active_rx_cnt = valid_rx_cnt;

	if (valid_rx_cnt < idle_rx_cnt)
		idle_rx_cnt = valid_rx_cnt;

	rx_chain |= active_rx_cnt << RXON_RX_CHAIN_MIMO_CNT_POS;
	rx_chain |= idle_rx_cnt  << RXON_RX_CHAIN_CNT_POS;

	ctx->staging.rx_chain = cpu_to_le16(rx_chain);

	if (!is_single && (active_rx_cnt >= IWL_NUM_RX_CHAINS_SINGLE) && is_cam)
		ctx->staging.rx_chain |= RXON_RX_CHAIN_MIMO_FORCE_MSK;
	else
		ctx->staging.rx_chain &= ~RXON_RX_CHAIN_MIMO_FORCE_MSK;

	IWL_DEBUG_ASSOC(priv, "rx_chain=0x%X active=%d idle=%d\n",
			ctx->staging.rx_chain,
			active_rx_cnt, idle_rx_cnt);

	WARN_ON(active_rx_cnt == 0 || idle_rx_cnt == 0 ||
		active_rx_cnt < idle_rx_cnt);
}