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
typedef  int u64 ;
typedef  int u32 ;
struct wmi_tlv_vdev_stats {int dummy; } ;
struct wmi_tlv_stats_ev {int /*<<< orphan*/  num_peer_stats_extd; int /*<<< orphan*/  stats_id; int /*<<< orphan*/  num_chan_stats; int /*<<< orphan*/  num_bcnflt_stats; int /*<<< orphan*/  num_peer_stats; int /*<<< orphan*/  num_vdev_stats; int /*<<< orphan*/  num_pdev_stats; } ;
struct wmi_tlv_peer_stats_extd {int /*<<< orphan*/  rx_duration_high; int /*<<< orphan*/  rx_duration; } ;
struct wmi_pdev_stats {int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; int /*<<< orphan*/  base; } ;
struct wmi_10x_peer_stats {int /*<<< orphan*/  peer_rx_rate; int /*<<< orphan*/  old; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ath10k_fw_stats_vdev {int /*<<< orphan*/  list; } ;
struct ath10k_fw_stats_peer {int rx_duration; int /*<<< orphan*/  list; void* peer_rx_rate; } ;
struct ath10k_fw_stats_pdev {int /*<<< orphan*/  list; } ;
struct ath10k_fw_stats {int /*<<< orphan*/  peers; int /*<<< orphan*/  vdevs; int /*<<< orphan*/  pdevs; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int EPROTO ; 
 unsigned long FIELD_GET (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (void const**) ; 
 int PTR_ERR (void const**) ; 
 int /*<<< orphan*/  WMI_TLV_PEER_RX_DURATION_HIGH_MASK ; 
 int /*<<< orphan*/  WMI_TLV_PEER_RX_DURATION_HIGH_VALID_BIT ; 
 int WMI_TLV_PEER_RX_DURATION_SHIFT ; 
 int WMI_TLV_STAT_PEER_EXTD ; 
 size_t WMI_TLV_TAG_ARRAY_BYTE ; 
 size_t WMI_TLV_TAG_STRUCT_STATS_EVENT ; 
 void* __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  ath10k_wmi_pull_pdev_stats_base (int /*<<< orphan*/ *,struct ath10k_fw_stats_pdev*) ; 
 int /*<<< orphan*/  ath10k_wmi_pull_pdev_stats_rx (int /*<<< orphan*/ *,struct ath10k_fw_stats_pdev*) ; 
 int /*<<< orphan*/  ath10k_wmi_pull_pdev_stats_tx (int /*<<< orphan*/ *,struct ath10k_fw_stats_pdev*) ; 
 int /*<<< orphan*/  ath10k_wmi_pull_peer_stats (int /*<<< orphan*/ *,struct ath10k_fw_stats_peer*) ; 
 size_t ath10k_wmi_tlv_len (void const*) ; 
 void** ath10k_wmi_tlv_parse_alloc (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_wmi_tlv_pull_vdev_stats (struct wmi_tlv_vdev_stats const*,struct ath10k_fw_stats_vdev*) ; 
 int /*<<< orphan*/  kfree (void const**) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int ath10k_wmi_tlv_op_pull_fw_stats(struct ath10k *ar,
					   struct sk_buff *skb,
					   struct ath10k_fw_stats *stats)
{
	const void **tb;
	const struct wmi_tlv_stats_ev *ev;
	u32 num_peer_stats_extd;
	const void *data;
	u32 num_pdev_stats;
	u32 num_vdev_stats;
	u32 num_peer_stats;
	u32 num_bcnflt_stats;
	u32 num_chan_stats;
	size_t data_len;
	u32 stats_id;
	int ret;
	int i;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	if (IS_ERR(tb)) {
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		return ret;
	}

	ev = tb[WMI_TLV_TAG_STRUCT_STATS_EVENT];
	data = tb[WMI_TLV_TAG_ARRAY_BYTE];

	if (!ev || !data) {
		kfree(tb);
		return -EPROTO;
	}

	data_len = ath10k_wmi_tlv_len(data);
	num_pdev_stats = __le32_to_cpu(ev->num_pdev_stats);
	num_vdev_stats = __le32_to_cpu(ev->num_vdev_stats);
	num_peer_stats = __le32_to_cpu(ev->num_peer_stats);
	num_bcnflt_stats = __le32_to_cpu(ev->num_bcnflt_stats);
	num_chan_stats = __le32_to_cpu(ev->num_chan_stats);
	stats_id = __le32_to_cpu(ev->stats_id);
	num_peer_stats_extd = __le32_to_cpu(ev->num_peer_stats_extd);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tlv stats update pdev %i vdev %i peer %i bcnflt %i chan %i peer_extd %i\n",
		   num_pdev_stats, num_vdev_stats, num_peer_stats,
		   num_bcnflt_stats, num_chan_stats, num_peer_stats_extd);

	for (i = 0; i < num_pdev_stats; i++) {
		const struct wmi_pdev_stats *src;
		struct ath10k_fw_stats_pdev *dst;

		src = data;
		if (data_len < sizeof(*src)) {
			kfree(tb);
			return -EPROTO;
		}

		data += sizeof(*src);
		data_len -= sizeof(*src);

		dst = kzalloc(sizeof(*dst), GFP_ATOMIC);
		if (!dst)
			continue;

		ath10k_wmi_pull_pdev_stats_base(&src->base, dst);
		ath10k_wmi_pull_pdev_stats_tx(&src->tx, dst);
		ath10k_wmi_pull_pdev_stats_rx(&src->rx, dst);
		list_add_tail(&dst->list, &stats->pdevs);
	}

	for (i = 0; i < num_vdev_stats; i++) {
		const struct wmi_tlv_vdev_stats *src;
		struct ath10k_fw_stats_vdev *dst;

		src = data;
		if (data_len < sizeof(*src)) {
			kfree(tb);
			return -EPROTO;
		}

		data += sizeof(*src);
		data_len -= sizeof(*src);

		dst = kzalloc(sizeof(*dst), GFP_ATOMIC);
		if (!dst)
			continue;

		ath10k_wmi_tlv_pull_vdev_stats(src, dst);
		list_add_tail(&dst->list, &stats->vdevs);
	}

	for (i = 0; i < num_peer_stats; i++) {
		const struct wmi_10x_peer_stats *src;
		struct ath10k_fw_stats_peer *dst;

		src = data;
		if (data_len < sizeof(*src)) {
			kfree(tb);
			return -EPROTO;
		}

		data += sizeof(*src);
		data_len -= sizeof(*src);

		dst = kzalloc(sizeof(*dst), GFP_ATOMIC);
		if (!dst)
			continue;

		ath10k_wmi_pull_peer_stats(&src->old, dst);
		dst->peer_rx_rate = __le32_to_cpu(src->peer_rx_rate);

		if (stats_id & WMI_TLV_STAT_PEER_EXTD) {
			const struct wmi_tlv_peer_stats_extd *extd;
			unsigned long rx_duration_high;

			extd = data + sizeof(*src) * (num_peer_stats - i - 1)
			       + sizeof(*extd) * i;

			dst->rx_duration = __le32_to_cpu(extd->rx_duration);
			rx_duration_high = __le32_to_cpu
						(extd->rx_duration_high);

			if (test_bit(WMI_TLV_PEER_RX_DURATION_HIGH_VALID_BIT,
				     &rx_duration_high)) {
				rx_duration_high =
					FIELD_GET(WMI_TLV_PEER_RX_DURATION_HIGH_MASK,
						  rx_duration_high);
				dst->rx_duration |= (u64)rx_duration_high <<
						    WMI_TLV_PEER_RX_DURATION_SHIFT;
			}
		}

		list_add_tail(&dst->list, &stats->peers);
	}

	kfree(tb);
	return 0;
}