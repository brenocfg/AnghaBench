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
struct sk_buff {scalar_t__ len; } ;
struct qtnf_wmac {struct qtnf_vif* iflist; } ;
struct TYPE_2__ {scalar_t__ iftype; } ;
struct qtnf_vif {struct net_device* netdev; TYPE_1__ wdev; } ;
struct qtnf_frame_meta_info {size_t magic_s; size_t magic_e; size_t macid; size_t ifidx; } ;
struct qtnf_bus {scalar_t__ fw_state; struct qtnf_wmac** mac; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_UNSPECIFIED ; 
 scalar_t__ QTNF_FW_STATE_RUNNING ; 
 size_t QTNF_MAX_INTF ; 
 size_t QTNF_MAX_MAC ; 
 int /*<<< orphan*/  __skb_trim (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,size_t,...) ; 
 int /*<<< orphan*/  qtnf_is_frame_meta_magic_valid (struct qtnf_frame_meta_info*) ; 
 int skb_tail_pointer (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

struct net_device *qtnf_classify_skb(struct qtnf_bus *bus, struct sk_buff *skb)
{
	struct qtnf_frame_meta_info *meta;
	struct net_device *ndev = NULL;
	struct qtnf_wmac *mac;
	struct qtnf_vif *vif;

	if (unlikely(bus->fw_state != QTNF_FW_STATE_RUNNING))
		return NULL;

	meta = (struct qtnf_frame_meta_info *)
		(skb_tail_pointer(skb) - sizeof(*meta));

	if (unlikely(!qtnf_is_frame_meta_magic_valid(meta))) {
		pr_err_ratelimited("invalid magic 0x%x:0x%x\n",
				   meta->magic_s, meta->magic_e);
		goto out;
	}

	if (unlikely(meta->macid >= QTNF_MAX_MAC)) {
		pr_err_ratelimited("invalid mac(%u)\n", meta->macid);
		goto out;
	}

	if (unlikely(meta->ifidx >= QTNF_MAX_INTF)) {
		pr_err_ratelimited("invalid vif(%u)\n", meta->ifidx);
		goto out;
	}

	mac = bus->mac[meta->macid];

	if (unlikely(!mac)) {
		pr_err_ratelimited("mac(%d) does not exist\n", meta->macid);
		goto out;
	}

	vif = &mac->iflist[meta->ifidx];

	if (unlikely(vif->wdev.iftype == NL80211_IFTYPE_UNSPECIFIED)) {
		pr_err_ratelimited("vif(%u) does not exists\n", meta->ifidx);
		goto out;
	}

	ndev = vif->netdev;

	if (unlikely(!ndev)) {
		pr_err_ratelimited("netdev for wlan%u.%u does not exists\n",
				   meta->macid, meta->ifidx);
		goto out;
	}

	__skb_trim(skb, skb->len - sizeof(*meta));

out:
	return ndev;
}