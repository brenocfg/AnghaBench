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
typedef  int u32 ;
struct wmi_vdev_stats_extd {int dummy; } ;
struct wmi_vdev_stats {int dummy; } ;
struct wmi_10_4_peer_stats {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct wmi_10_4_peer_extd_stats {int /*<<< orphan*/  rx_duration; TYPE_1__ peer_macaddr; } ;
struct wmi_10_4_pdev_stats {int /*<<< orphan*/  extra; int /*<<< orphan*/  rx_ovfl_errs; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; int /*<<< orphan*/  base; } ;
struct wmi_10_4_bss_bcn_filter_stats {int dummy; } ;
struct wmi_10_2_stats_event {int /*<<< orphan*/  stats_id; int /*<<< orphan*/  num_bcnflt_stats; int /*<<< orphan*/  num_peer_stats; int /*<<< orphan*/  num_vdev_stats; int /*<<< orphan*/  num_pdev_ext_stats; int /*<<< orphan*/  num_pdev_stats; } ;
struct wmi_10_2_pdev_ext_stats {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k_fw_stats_vdev_extd {int /*<<< orphan*/  list; } ;
struct ath10k_fw_stats_peer {int /*<<< orphan*/  list; } ;
struct ath10k_fw_stats_pdev {int /*<<< orphan*/  list; void* rx_ovfl_errs; } ;
struct ath10k_fw_stats {int extended; int /*<<< orphan*/  vdevs; int /*<<< orphan*/  peers_extd; int /*<<< orphan*/  peers; int /*<<< orphan*/  pdevs; } ;
struct ath10k_fw_extd_stats_peer {int /*<<< orphan*/  list; void* rx_duration; int /*<<< orphan*/  peer_macaddr; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int WMI_10_4_STAT_PEER_EXTD ; 
 int WMI_10_4_STAT_VDEV_EXTD ; 
 void* __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_wmi_10_4_pull_pdev_stats_tx (int /*<<< orphan*/ *,struct ath10k_fw_stats_pdev*) ; 
 int /*<<< orphan*/  ath10k_wmi_10_4_pull_peer_stats (struct wmi_10_4_peer_stats const*,struct ath10k_fw_stats_peer*) ; 
 int /*<<< orphan*/  ath10k_wmi_10_4_pull_vdev_stats (struct wmi_vdev_stats_extd const*,struct ath10k_fw_stats_vdev_extd*) ; 
 int /*<<< orphan*/  ath10k_wmi_pull_pdev_stats_base (int /*<<< orphan*/ *,struct ath10k_fw_stats_pdev*) ; 
 int /*<<< orphan*/  ath10k_wmi_pull_pdev_stats_extra (int /*<<< orphan*/ *,struct ath10k_fw_stats_pdev*) ; 
 int /*<<< orphan*/  ath10k_wmi_pull_pdev_stats_rx (int /*<<< orphan*/ *,struct ath10k_fw_stats_pdev*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int ath10k_wmi_10_4_op_pull_fw_stats(struct ath10k *ar,
					    struct sk_buff *skb,
					    struct ath10k_fw_stats *stats)
{
	const struct wmi_10_2_stats_event *ev = (void *)skb->data;
	u32 num_pdev_stats;
	u32 num_pdev_ext_stats;
	u32 num_vdev_stats;
	u32 num_peer_stats;
	u32 num_bcnflt_stats;
	u32 stats_id;
	int i;

	if (!skb_pull(skb, sizeof(*ev)))
		return -EPROTO;

	num_pdev_stats = __le32_to_cpu(ev->num_pdev_stats);
	num_pdev_ext_stats = __le32_to_cpu(ev->num_pdev_ext_stats);
	num_vdev_stats = __le32_to_cpu(ev->num_vdev_stats);
	num_peer_stats = __le32_to_cpu(ev->num_peer_stats);
	num_bcnflt_stats = __le32_to_cpu(ev->num_bcnflt_stats);
	stats_id = __le32_to_cpu(ev->stats_id);

	for (i = 0; i < num_pdev_stats; i++) {
		const struct wmi_10_4_pdev_stats *src;
		struct ath10k_fw_stats_pdev *dst;

		src = (void *)skb->data;
		if (!skb_pull(skb, sizeof(*src)))
			return -EPROTO;

		dst = kzalloc(sizeof(*dst), GFP_ATOMIC);
		if (!dst)
			continue;

		ath10k_wmi_pull_pdev_stats_base(&src->base, dst);
		ath10k_wmi_10_4_pull_pdev_stats_tx(&src->tx, dst);
		ath10k_wmi_pull_pdev_stats_rx(&src->rx, dst);
		dst->rx_ovfl_errs = __le32_to_cpu(src->rx_ovfl_errs);
		ath10k_wmi_pull_pdev_stats_extra(&src->extra, dst);

		list_add_tail(&dst->list, &stats->pdevs);
	}

	for (i = 0; i < num_pdev_ext_stats; i++) {
		const struct wmi_10_2_pdev_ext_stats *src;

		src = (void *)skb->data;
		if (!skb_pull(skb, sizeof(*src)))
			return -EPROTO;

		/* FIXME: expose values to userspace
		 *
		 * Note: Even though this loop seems to do nothing it is
		 * required to parse following sub-structures properly.
		 */
	}

	for (i = 0; i < num_vdev_stats; i++) {
		const struct wmi_vdev_stats *src;

		/* Ignore vdev stats here as it has only vdev id. Actual vdev
		 * stats will be retrieved from vdev extended stats.
		 */
		src = (void *)skb->data;
		if (!skb_pull(skb, sizeof(*src)))
			return -EPROTO;
	}

	for (i = 0; i < num_peer_stats; i++) {
		const struct wmi_10_4_peer_stats *src;
		struct ath10k_fw_stats_peer *dst;

		src = (void *)skb->data;
		if (!skb_pull(skb, sizeof(*src)))
			return -EPROTO;

		dst = kzalloc(sizeof(*dst), GFP_ATOMIC);
		if (!dst)
			continue;

		ath10k_wmi_10_4_pull_peer_stats(src, dst);
		list_add_tail(&dst->list, &stats->peers);
	}

	for (i = 0; i < num_bcnflt_stats; i++) {
		const struct wmi_10_4_bss_bcn_filter_stats *src;

		src = (void *)skb->data;
		if (!skb_pull(skb, sizeof(*src)))
			return -EPROTO;

		/* FIXME: expose values to userspace
		 *
		 * Note: Even though this loop seems to do nothing it is
		 * required to parse following sub-structures properly.
		 */
	}

	if (stats_id & WMI_10_4_STAT_PEER_EXTD) {
		stats->extended = true;

		for (i = 0; i < num_peer_stats; i++) {
			const struct wmi_10_4_peer_extd_stats *src;
			struct ath10k_fw_extd_stats_peer *dst;

			src = (void *)skb->data;
			if (!skb_pull(skb, sizeof(*src)))
				return -EPROTO;

			dst = kzalloc(sizeof(*dst), GFP_ATOMIC);
			if (!dst)
				continue;

			ether_addr_copy(dst->peer_macaddr,
					src->peer_macaddr.addr);
			dst->rx_duration = __le32_to_cpu(src->rx_duration);
			list_add_tail(&dst->list, &stats->peers_extd);
		}
	}

	if (stats_id & WMI_10_4_STAT_VDEV_EXTD) {
		for (i = 0; i < num_vdev_stats; i++) {
			const struct wmi_vdev_stats_extd *src;
			struct ath10k_fw_stats_vdev_extd *dst;

			src = (void *)skb->data;
			if (!skb_pull(skb, sizeof(*src)))
				return -EPROTO;

			dst = kzalloc(sizeof(*dst), GFP_ATOMIC);
			if (!dst)
				continue;
			ath10k_wmi_10_4_pull_vdev_stats(src, dst);
			list_add_tail(&dst->list, &stats->vdevs);
		}
	}

	return 0;
}