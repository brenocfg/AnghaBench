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
typedef  size_t u8 ;
typedef  int u16 ;
struct wmi_delete_pstream_cmd {size_t traffic_class; size_t tsid; } ;
struct wmi {int* stream_exist_for_ac; int fat_pipe_exist; int /*<<< orphan*/  parent_dev; int /*<<< orphan*/  lock; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int EINVAL ; 
 int ENODATA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SYNC_BEFORE_WMIFLAG ; 
 int /*<<< orphan*/  WMI_DELETE_PSTREAM_CMDID ; 
 size_t WMM_NUM_AC ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 int /*<<< orphan*/  ath6kl_err (char*,size_t) ; 
 int /*<<< orphan*/  ath6kl_indicate_tx_activity (int /*<<< orphan*/ ,size_t,int) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,size_t,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int ath6kl_wmi_delete_pstream_cmd(struct wmi *wmi, u8 if_idx, u8 traffic_class,
				  u8 tsid)
{
	struct sk_buff *skb;
	struct wmi_delete_pstream_cmd *cmd;
	u16 active_tsids = 0;
	int ret;

	if (traffic_class >= WMM_NUM_AC) {
		ath6kl_err("invalid traffic class: %d\n", traffic_class);
		return -EINVAL;
	}

	skb = ath6kl_wmi_get_new_buf(sizeof(*cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct wmi_delete_pstream_cmd *) skb->data;
	cmd->traffic_class = traffic_class;
	cmd->tsid = tsid;

	spin_lock_bh(&wmi->lock);
	active_tsids = wmi->stream_exist_for_ac[traffic_class];
	spin_unlock_bh(&wmi->lock);

	if (!(active_tsids & (1 << tsid))) {
		dev_kfree_skb(skb);
		ath6kl_dbg(ATH6KL_DBG_WMI,
			   "TSID %d doesn't exist for traffic class: %d\n",
			   tsid, traffic_class);
		return -ENODATA;
	}

	ath6kl_dbg(ATH6KL_DBG_WMI,
		   "sending delete_pstream_cmd: traffic class: %d tsid=%d\n",
		   traffic_class, tsid);

	ret = ath6kl_wmi_cmd_send(wmi, if_idx, skb, WMI_DELETE_PSTREAM_CMDID,
				  SYNC_BEFORE_WMIFLAG);

	spin_lock_bh(&wmi->lock);
	wmi->stream_exist_for_ac[traffic_class] &= ~(1 << tsid);
	active_tsids = wmi->stream_exist_for_ac[traffic_class];
	spin_unlock_bh(&wmi->lock);

	/*
	 * Indicate stream inactivity to driver layer only if all tsids
	 * within this AC are deleted.
	 */
	if (!active_tsids) {
		ath6kl_indicate_tx_activity(wmi->parent_dev,
					    traffic_class, false);
		wmi->fat_pipe_exist &= ~(1 << traffic_class);
	}

	return ret;
}