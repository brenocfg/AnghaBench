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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ data; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; } ;
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; int /*<<< orphan*/  flags; struct ath6kl* ar; } ;
struct ath6kl_sta {int sta_flags; int apsd_info; int /*<<< orphan*/  aid; int /*<<< orphan*/  psq_lock; int /*<<< orphan*/  apsdq; } ;
struct ath6kl_llc_snap_hdr {int /*<<< orphan*/  eth_type; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 scalar_t__ IP_ETHERTYPE ; 
 int STA_PS_APSD_EOSP ; 
 int STA_PS_APSD_TRIGGER ; 
 int /*<<< orphan*/  WMI_DATA_HDR_FLAGS_EOSP ; 
 int /*<<< orphan*/  WMI_DATA_HDR_FLAGS_MORE ; 
 int /*<<< orphan*/  WMI_DATA_HDR_FLAGS_UAPSD ; 
 int /*<<< orphan*/  WMM_ENABLED ; 
 int ath6kl_wmi_determine_user_priority (int*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_get_traffic_class (int) ; 
 int /*<<< orphan*/  ath6kl_wmi_set_apsd_bfrd_traf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ethertype (scalar_t__) ; 
 int skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ath6kl_process_uapsdq(struct ath6kl_sta *conn,
				struct ath6kl_vif *vif,
				struct sk_buff *skb,
				u32 *flags)
{
	struct ath6kl *ar = vif->ar;
	bool is_apsdq_empty = false;
	struct ethhdr *datap = (struct ethhdr *) skb->data;
	u8 up = 0, traffic_class, *ip_hdr;
	u16 ether_type;
	struct ath6kl_llc_snap_hdr *llc_hdr;

	if (conn->sta_flags & STA_PS_APSD_TRIGGER) {
		/*
		 * This tx is because of a uAPSD trigger, determine
		 * more and EOSP bit. Set EOSP if queue is empty
		 * or sufficient frames are delivered for this trigger.
		 */
		spin_lock_bh(&conn->psq_lock);
		if (!skb_queue_empty(&conn->apsdq))
			*flags |= WMI_DATA_HDR_FLAGS_MORE;
		else if (conn->sta_flags & STA_PS_APSD_EOSP)
			*flags |= WMI_DATA_HDR_FLAGS_EOSP;
		*flags |= WMI_DATA_HDR_FLAGS_UAPSD;
		spin_unlock_bh(&conn->psq_lock);
		return false;
	} else if (!conn->apsd_info) {
		return false;
	}

	if (test_bit(WMM_ENABLED, &vif->flags)) {
		ether_type = be16_to_cpu(datap->h_proto);
		if (is_ethertype(ether_type)) {
			/* packet is in DIX format  */
			ip_hdr = (u8 *)(datap + 1);
		} else {
			/* packet is in 802.3 format */
			llc_hdr = (struct ath6kl_llc_snap_hdr *)
							(datap + 1);
			ether_type = be16_to_cpu(llc_hdr->eth_type);
			ip_hdr = (u8 *)(llc_hdr + 1);
		}

		if (ether_type == IP_ETHERTYPE)
			up = ath6kl_wmi_determine_user_priority(
							ip_hdr, 0);
	}

	traffic_class = ath6kl_wmi_get_traffic_class(up);

	if ((conn->apsd_info & (1 << traffic_class)) == 0)
		return false;

	/* Queue the frames if the STA is sleeping */
	spin_lock_bh(&conn->psq_lock);
	is_apsdq_empty = skb_queue_empty(&conn->apsdq);
	skb_queue_tail(&conn->apsdq, skb);
	spin_unlock_bh(&conn->psq_lock);

	/*
	 * If this is the first pkt getting queued
	 * for this STA, update the PVB for this STA
	 */
	if (is_apsdq_empty) {
		ath6kl_wmi_set_apsd_bfrd_traf(ar->wmi,
					      vif->fw_vif_idx,
					      conn->aid, 1, 0);
	}
	*flags |= WMI_DATA_HDR_FLAGS_UAPSD;

	return true;
}