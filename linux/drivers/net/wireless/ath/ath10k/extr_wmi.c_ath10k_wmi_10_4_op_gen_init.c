#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct wmi_resource_config_10_4 {void* qwrap_config; void* iphdr_pad_config; void* atf_config; void* tt_support; void* rx_batchmode; void* vo_minfree; void* vi_minfree; void* be_minfree; void* bk_minfree; void* smart_ant_cap; void* max_peer_ext_stats; void* max_frag_entries; void* num_msdu_desc; void* gtk_offload_max_vdev; void* vow_config; void* rx_skip_defrag_timeout_dup_detection_check; void* mac_aggr_delim; void* dma_burst_size; void* num_wds_entries; void* tx_dbg_log_size; void* mcast2ucast_mode; void* num_mcast_table_elems; void* num_mcast_groups; void* roam_offload_max_ap_profiles; void* roam_offload_max_vdev; void* bmiss_offload_max_vdev; void* scan_max_pending_req; void* rx_decap_mode; void** rx_timeout_pri; void* rx_chain_mask; void* tx_chain_mask; void* ast_skid_limit; void* num_peer_keys; void* num_offload_reorder_buffs; void* num_offload_peers; void* num_tids; void* num_active_peers; void* num_peers; void* num_vdevs; } ;
struct wmi_init_cmd_10_4 {int /*<<< orphan*/  mem_chunks; int /*<<< orphan*/  resource_config; } ;
struct sk_buff {scalar_t__ data; } ;
struct host_memory_chunk {int dummy; } ;
struct TYPE_6__ {int num_mem_chunks; int /*<<< orphan*/  rx_decap_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  max_num_pending_tx; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_chain_mask; int /*<<< orphan*/  tx_chain_mask; } ;
struct ath10k {TYPE_3__ wmi; TYPE_2__ htt; TYPE_1__ hw_params; int /*<<< orphan*/  num_tids; int /*<<< orphan*/  num_active_peers; int /*<<< orphan*/  max_num_peers; int /*<<< orphan*/  max_num_vdevs; } ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_10_4_11AC_TX_MAX_FRAGS ; 
 int /*<<< orphan*/  TARGET_10_4_AST_SKID_LIMIT ; 
 int /*<<< orphan*/  TARGET_10_4_ATF_CONFIG ; 
 int /*<<< orphan*/  TARGET_10_4_BE_MIN_FREE ; 
 int /*<<< orphan*/  TARGET_10_4_BK_MIN_FREE ; 
 int /*<<< orphan*/  TARGET_10_4_BMISS_OFFLOAD_MAX_VDEV ; 
 int /*<<< orphan*/  TARGET_10_4_DMA_BURST_SIZE ; 
 int /*<<< orphan*/  TARGET_10_4_GTK_OFFLOAD_MAX_VDEV ; 
 int /*<<< orphan*/  TARGET_10_4_IPHDR_PAD_CONFIG ; 
 int /*<<< orphan*/  TARGET_10_4_MAC_AGGR_DELIM ; 
 int /*<<< orphan*/  TARGET_10_4_MAX_PEER_EXT_STATS ; 
 int /*<<< orphan*/  TARGET_10_4_MCAST2UCAST_MODE ; 
 int /*<<< orphan*/  TARGET_10_4_NUM_MCAST_GROUPS ; 
 int /*<<< orphan*/  TARGET_10_4_NUM_MCAST_TABLE_ELEMS ; 
 int /*<<< orphan*/  TARGET_10_4_NUM_OFFLOAD_PEERS ; 
 int /*<<< orphan*/  TARGET_10_4_NUM_OFFLOAD_REORDER_BUFFS ; 
 int /*<<< orphan*/  TARGET_10_4_NUM_PEER_KEYS ; 
 int /*<<< orphan*/  TARGET_10_4_NUM_WDS_ENTRIES ; 
 int /*<<< orphan*/  TARGET_10_4_QWRAP_CONFIG ; 
 int /*<<< orphan*/  TARGET_10_4_ROAM_OFFLOAD_MAX_PROFILES ; 
 int /*<<< orphan*/  TARGET_10_4_ROAM_OFFLOAD_MAX_VDEV ; 
 int /*<<< orphan*/  TARGET_10_4_RX_BATCH_MODE ; 
 int /*<<< orphan*/  TARGET_10_4_RX_SKIP_DEFRAG_TIMEOUT_DUP_DETECTION_CHECK ; 
 int /*<<< orphan*/  TARGET_10_4_RX_TIMEOUT_HI_PRI ; 
 int /*<<< orphan*/  TARGET_10_4_RX_TIMEOUT_LO_PRI ; 
 int /*<<< orphan*/  TARGET_10_4_SCAN_MAX_REQS ; 
 int /*<<< orphan*/  TARGET_10_4_SMART_ANT_CAP ; 
 int /*<<< orphan*/  TARGET_10_4_THERMAL_THROTTLING_CONFIG ; 
 int /*<<< orphan*/  TARGET_10_4_TX_DBG_LOG_SIZE ; 
 int /*<<< orphan*/  TARGET_10_4_VI_MIN_FREE ; 
 int /*<<< orphan*/  TARGET_10_4_VOW_CONFIG ; 
 int /*<<< orphan*/  TARGET_10_4_VO_MIN_FREE ; 
 void* __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 
 int /*<<< orphan*/  ath10k_wmi_put_host_mem_chunks (struct ath10k*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct wmi_resource_config_10_4*,int) ; 

__attribute__((used)) static struct sk_buff *ath10k_wmi_10_4_op_gen_init(struct ath10k *ar)
{
	struct wmi_init_cmd_10_4 *cmd;
	struct sk_buff *buf;
	struct wmi_resource_config_10_4 config = {};
	u32 len;

	config.num_vdevs = __cpu_to_le32(ar->max_num_vdevs);
	config.num_peers = __cpu_to_le32(ar->max_num_peers);
	config.num_active_peers = __cpu_to_le32(ar->num_active_peers);
	config.num_tids = __cpu_to_le32(ar->num_tids);

	config.num_offload_peers = __cpu_to_le32(TARGET_10_4_NUM_OFFLOAD_PEERS);
	config.num_offload_reorder_buffs =
			__cpu_to_le32(TARGET_10_4_NUM_OFFLOAD_REORDER_BUFFS);
	config.num_peer_keys  = __cpu_to_le32(TARGET_10_4_NUM_PEER_KEYS);
	config.ast_skid_limit = __cpu_to_le32(TARGET_10_4_AST_SKID_LIMIT);
	config.tx_chain_mask  = __cpu_to_le32(ar->hw_params.tx_chain_mask);
	config.rx_chain_mask  = __cpu_to_le32(ar->hw_params.rx_chain_mask);

	config.rx_timeout_pri[0] = __cpu_to_le32(TARGET_10_4_RX_TIMEOUT_LO_PRI);
	config.rx_timeout_pri[1] = __cpu_to_le32(TARGET_10_4_RX_TIMEOUT_LO_PRI);
	config.rx_timeout_pri[2] = __cpu_to_le32(TARGET_10_4_RX_TIMEOUT_LO_PRI);
	config.rx_timeout_pri[3] = __cpu_to_le32(TARGET_10_4_RX_TIMEOUT_HI_PRI);

	config.rx_decap_mode	    = __cpu_to_le32(ar->wmi.rx_decap_mode);
	config.scan_max_pending_req = __cpu_to_le32(TARGET_10_4_SCAN_MAX_REQS);
	config.bmiss_offload_max_vdev =
			__cpu_to_le32(TARGET_10_4_BMISS_OFFLOAD_MAX_VDEV);
	config.roam_offload_max_vdev  =
			__cpu_to_le32(TARGET_10_4_ROAM_OFFLOAD_MAX_VDEV);
	config.roam_offload_max_ap_profiles =
			__cpu_to_le32(TARGET_10_4_ROAM_OFFLOAD_MAX_PROFILES);
	config.num_mcast_groups = __cpu_to_le32(TARGET_10_4_NUM_MCAST_GROUPS);
	config.num_mcast_table_elems =
			__cpu_to_le32(TARGET_10_4_NUM_MCAST_TABLE_ELEMS);

	config.mcast2ucast_mode = __cpu_to_le32(TARGET_10_4_MCAST2UCAST_MODE);
	config.tx_dbg_log_size  = __cpu_to_le32(TARGET_10_4_TX_DBG_LOG_SIZE);
	config.num_wds_entries  = __cpu_to_le32(TARGET_10_4_NUM_WDS_ENTRIES);
	config.dma_burst_size   = __cpu_to_le32(TARGET_10_4_DMA_BURST_SIZE);
	config.mac_aggr_delim   = __cpu_to_le32(TARGET_10_4_MAC_AGGR_DELIM);

	config.rx_skip_defrag_timeout_dup_detection_check =
	  __cpu_to_le32(TARGET_10_4_RX_SKIP_DEFRAG_TIMEOUT_DUP_DETECTION_CHECK);

	config.vow_config = __cpu_to_le32(TARGET_10_4_VOW_CONFIG);
	config.gtk_offload_max_vdev =
			__cpu_to_le32(TARGET_10_4_GTK_OFFLOAD_MAX_VDEV);
	config.num_msdu_desc = __cpu_to_le32(ar->htt.max_num_pending_tx);
	config.max_frag_entries = __cpu_to_le32(TARGET_10_4_11AC_TX_MAX_FRAGS);
	config.max_peer_ext_stats =
			__cpu_to_le32(TARGET_10_4_MAX_PEER_EXT_STATS);
	config.smart_ant_cap = __cpu_to_le32(TARGET_10_4_SMART_ANT_CAP);

	config.bk_minfree = __cpu_to_le32(TARGET_10_4_BK_MIN_FREE);
	config.be_minfree = __cpu_to_le32(TARGET_10_4_BE_MIN_FREE);
	config.vi_minfree = __cpu_to_le32(TARGET_10_4_VI_MIN_FREE);
	config.vo_minfree = __cpu_to_le32(TARGET_10_4_VO_MIN_FREE);

	config.rx_batchmode = __cpu_to_le32(TARGET_10_4_RX_BATCH_MODE);
	config.tt_support =
			__cpu_to_le32(TARGET_10_4_THERMAL_THROTTLING_CONFIG);
	config.atf_config = __cpu_to_le32(TARGET_10_4_ATF_CONFIG);
	config.iphdr_pad_config = __cpu_to_le32(TARGET_10_4_IPHDR_PAD_CONFIG);
	config.qwrap_config = __cpu_to_le32(TARGET_10_4_QWRAP_CONFIG);

	len = sizeof(*cmd) +
	      (sizeof(struct host_memory_chunk) * ar->wmi.num_mem_chunks);

	buf = ath10k_wmi_alloc_skb(ar, len);
	if (!buf)
		return ERR_PTR(-ENOMEM);

	cmd = (struct wmi_init_cmd_10_4 *)buf->data;
	memcpy(&cmd->resource_config, &config, sizeof(config));
	ath10k_wmi_put_host_mem_chunks(ar, &cmd->mem_chunks);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi init 10.4\n");
	return buf;
}