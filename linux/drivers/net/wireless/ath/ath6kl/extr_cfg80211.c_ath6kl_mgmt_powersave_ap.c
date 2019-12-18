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
typedef  void* u32 ;
struct ieee80211_mgmt {int /*<<< orphan*/  da; } ;
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; struct ath6kl* ar; } ;
struct ath6kl_sta {int sta_flags; scalar_t__ mgmt_psq_len; int /*<<< orphan*/  psq_lock; int /*<<< orphan*/  psq; int /*<<< orphan*/  aid; int /*<<< orphan*/  mgmt_psq; } ;
struct ath6kl_mgmt_buff {size_t len; int no_cck; int /*<<< orphan*/  list; int /*<<< orphan*/  buf; void* wait; void* freq; void* id; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int STA_PS_POLLED ; 
 int STA_PS_SLEEP ; 
 struct ath6kl_sta* ath6kl_find_sta (struct ath6kl_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_wmi_set_pvb_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 struct ath6kl_mgmt_buff* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ath6kl_mgmt_powersave_ap(struct ath6kl_vif *vif,
				     u32 id,
				     u32 freq,
				     u32 wait,
				     const u8 *buf,
				     size_t len,
				     bool *more_data,
				     bool no_cck)
{
	struct ieee80211_mgmt *mgmt;
	struct ath6kl_sta *conn;
	bool is_psq_empty = false;
	struct ath6kl_mgmt_buff *mgmt_buf;
	size_t mgmt_buf_size;
	struct ath6kl *ar = vif->ar;

	mgmt = (struct ieee80211_mgmt *) buf;
	if (is_multicast_ether_addr(mgmt->da))
		return false;

	conn = ath6kl_find_sta(vif, mgmt->da);
	if (!conn)
		return false;

	if (conn->sta_flags & STA_PS_SLEEP) {
		if (!(conn->sta_flags & STA_PS_POLLED)) {
			/* Queue the frames if the STA is sleeping */
			mgmt_buf_size = len + sizeof(struct ath6kl_mgmt_buff);
			mgmt_buf = kmalloc(mgmt_buf_size, GFP_KERNEL);
			if (!mgmt_buf)
				return false;

			INIT_LIST_HEAD(&mgmt_buf->list);
			mgmt_buf->id = id;
			mgmt_buf->freq = freq;
			mgmt_buf->wait = wait;
			mgmt_buf->len = len;
			mgmt_buf->no_cck = no_cck;
			memcpy(mgmt_buf->buf, buf, len);
			spin_lock_bh(&conn->psq_lock);
			is_psq_empty = skb_queue_empty(&conn->psq) &&
					(conn->mgmt_psq_len == 0);
			list_add_tail(&mgmt_buf->list, &conn->mgmt_psq);
			conn->mgmt_psq_len++;
			spin_unlock_bh(&conn->psq_lock);

			/*
			 * If this is the first pkt getting queued
			 * for this STA, update the PVB for this
			 * STA.
			 */
			if (is_psq_empty)
				ath6kl_wmi_set_pvb_cmd(ar->wmi, vif->fw_vif_idx,
						       conn->aid, 1);
			return true;
		}

		/*
		 * This tx is because of a PsPoll.
		 * Determine if MoreData bit has to be set.
		 */
		spin_lock_bh(&conn->psq_lock);
		if (!skb_queue_empty(&conn->psq) || (conn->mgmt_psq_len != 0))
			*more_data = true;
		spin_unlock_bh(&conn->psq_lock);
	}

	return false;
}