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
struct wmi_tlv {scalar_t__ value; } ;
struct wmi_peer_delete_resp_ev_arg {int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  vdev_id; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int /*<<< orphan*/  peer_delete_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_wmi_tlv_event_peer_delete_resp(struct ath10k *ar,
						 struct sk_buff *skb)
{
	struct wmi_peer_delete_resp_ev_arg *arg;
	struct wmi_tlv *tlv_hdr;

	tlv_hdr = (struct wmi_tlv *)skb->data;
	arg = (struct wmi_peer_delete_resp_ev_arg *)tlv_hdr->value;

	ath10k_dbg(ar, ATH10K_DBG_WMI, "vdev id %d", arg->vdev_id);
	ath10k_dbg(ar, ATH10K_DBG_WMI, "peer mac addr %pM", &arg->peer_addr);
	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv peer delete response\n");

	complete(&ar->peer_delete_done);

	return 0;
}