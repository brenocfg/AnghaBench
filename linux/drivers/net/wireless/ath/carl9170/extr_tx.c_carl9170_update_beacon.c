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
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct carl9170_vif_info {scalar_t__ id; struct sk_buff* beacon; } ;
struct TYPE_3__ {scalar_t__ beacon_addr; scalar_t__ beacon_max_len; } ;
struct ar9170 {int /*<<< orphan*/  beacon_lock; TYPE_2__* hw; TYPE_1__ fw; } ;
typedef  scalar_t__ __le32 ;
struct TYPE_4__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 scalar_t__ AR9170_MAC_BCN_LENGTH_MAX ; 
 scalar_t__ AR9170_MAC_REG_BCN_HT1 ; 
 scalar_t__ AR9170_MAC_REG_BCN_HT2 ; 
 scalar_t__ AR9170_MAC_REG_BCN_PLCP ; 
 int /*<<< orphan*/  CARL9170_BCN_CTRL_CAB_TRIGGER ; 
 int DIV_ROUND_UP (scalar_t__,int) ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 scalar_t__ FCS_LEN ; 
 int /*<<< orphan*/  carl9170_async_regwrite (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  carl9170_async_regwrite_begin (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_async_regwrite_finish () ; 
 int carl9170_async_regwrite_result () ; 
 int carl9170_bcn_ctrl (struct ar9170*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  carl9170_get_vif (struct carl9170_vif_info*) ; 
 struct carl9170_vif_info* carl9170_pick_beaconing_vif (struct ar9170*) ; 
 int carl9170_tx_beacon_physet (struct ar9170*,struct sk_buff*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* ieee80211_beacon_get_tim (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ roundup (scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,...) ; 

int carl9170_update_beacon(struct ar9170 *ar, const bool submit)
{
	struct sk_buff *skb = NULL;
	struct carl9170_vif_info *cvif;
	__le32 *data, *old = NULL;
	u32 word, ht1, plcp, off, addr, len;
	int i = 0, err = 0;
	bool ht_rate;

	rcu_read_lock();
	cvif = carl9170_pick_beaconing_vif(ar);
	if (!cvif)
		goto out_unlock;

	skb = ieee80211_beacon_get_tim(ar->hw, carl9170_get_vif(cvif),
		NULL, NULL);

	if (!skb) {
		err = -ENOMEM;
		goto err_free;
	}

	spin_lock_bh(&ar->beacon_lock);
	data = (__le32 *)skb->data;
	if (cvif->beacon)
		old = (__le32 *)cvif->beacon->data;

	off = cvif->id * AR9170_MAC_BCN_LENGTH_MAX;
	addr = ar->fw.beacon_addr + off;
	len = roundup(skb->len + FCS_LEN, 4);

	if ((off + len) > ar->fw.beacon_max_len) {
		if (net_ratelimit()) {
			wiphy_err(ar->hw->wiphy, "beacon does not "
				  "fit into device memory!\n");
		}
		err = -EINVAL;
		goto err_unlock;
	}

	if (len > AR9170_MAC_BCN_LENGTH_MAX) {
		if (net_ratelimit()) {
			wiphy_err(ar->hw->wiphy, "no support for beacons "
				"bigger than %d (yours:%d).\n",
				 AR9170_MAC_BCN_LENGTH_MAX, len);
		}

		err = -EMSGSIZE;
		goto err_unlock;
	}

	ht_rate = carl9170_tx_beacon_physet(ar, skb, &ht1, &plcp);

	carl9170_async_regwrite_begin(ar);
	carl9170_async_regwrite(AR9170_MAC_REG_BCN_HT1, ht1);
	if (ht_rate)
		carl9170_async_regwrite(AR9170_MAC_REG_BCN_HT2, plcp);
	else
		carl9170_async_regwrite(AR9170_MAC_REG_BCN_PLCP, plcp);

	for (i = 0; i < DIV_ROUND_UP(skb->len, 4); i++) {
		/*
		 * XXX: This accesses beyond skb data for up
		 *	to the last 3 bytes!!
		 */

		if (old && (data[i] == old[i]))
			continue;

		word = le32_to_cpu(data[i]);
		carl9170_async_regwrite(addr + 4 * i, word);
	}
	carl9170_async_regwrite_finish();

	dev_kfree_skb_any(cvif->beacon);
	cvif->beacon = NULL;

	err = carl9170_async_regwrite_result();
	if (!err)
		cvif->beacon = skb;
	spin_unlock_bh(&ar->beacon_lock);
	if (err)
		goto err_free;

	if (submit) {
		err = carl9170_bcn_ctrl(ar, cvif->id,
					CARL9170_BCN_CTRL_CAB_TRIGGER,
					addr, skb->len + FCS_LEN);

		if (err)
			goto err_free;
	}
out_unlock:
	rcu_read_unlock();
	return 0;

err_unlock:
	spin_unlock_bh(&ar->beacon_lock);

err_free:
	rcu_read_unlock();
	dev_kfree_skb_any(skb);
	return err;
}