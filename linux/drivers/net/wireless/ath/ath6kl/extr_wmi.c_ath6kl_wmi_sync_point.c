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
struct wmi_sync_cmd {int data_sync_map; } ;
struct wmi_data_sync_bufs {int traffic_class; int /*<<< orphan*/ * skb; } ;
struct wmi {int fat_pipe_exist; int /*<<< orphan*/  parent_dev; int /*<<< orphan*/  lock; } ;
struct sk_buff {scalar_t__ data; } ;
typedef  enum htc_endpoint_id { ____Placeholder_htc_endpoint_id } htc_endpoint_id ;
typedef  int /*<<< orphan*/  data_sync_bufs ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WMI_SYNCHRONIZE_CMDID ; 
 int WMM_NUM_AC ; 
 int ath6kl_ac2_endpoint_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ath6kl_buf_alloc (int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_data_sync_send (struct wmi*,int /*<<< orphan*/ *,int,int) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct wmi_data_sync_bufs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath6kl_wmi_sync_point(struct wmi *wmi, u8 if_idx)
{
	struct sk_buff *skb;
	struct wmi_sync_cmd *cmd;
	struct wmi_data_sync_bufs data_sync_bufs[WMM_NUM_AC];
	enum htc_endpoint_id ep_id;
	u8 index, num_pri_streams = 0;
	int ret = 0;

	memset(data_sync_bufs, 0, sizeof(data_sync_bufs));

	spin_lock_bh(&wmi->lock);

	for (index = 0; index < WMM_NUM_AC; index++) {
		if (wmi->fat_pipe_exist & (1 << index)) {
			num_pri_streams++;
			data_sync_bufs[num_pri_streams - 1].traffic_class =
			    index;
		}
	}

	spin_unlock_bh(&wmi->lock);

	skb = ath6kl_wmi_get_new_buf(sizeof(*cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct wmi_sync_cmd *) skb->data;

	/*
	 * In the SYNC cmd sent on the control Ep, send a bitmap
	 * of the data eps on which the Data Sync will be sent
	 */
	cmd->data_sync_map = wmi->fat_pipe_exist;

	for (index = 0; index < num_pri_streams; index++) {
		data_sync_bufs[index].skb = ath6kl_buf_alloc(0);
		if (data_sync_bufs[index].skb == NULL) {
			ret = -ENOMEM;
			break;
		}
	}

	/*
	 * If buffer allocation for any of the dataSync fails,
	 * then do not send the Synchronize cmd on the control ep
	 */
	if (ret)
		goto free_cmd_skb;

	/*
	 * Send sync cmd followed by sync data messages on all
	 * endpoints being used
	 */
	ret = ath6kl_wmi_cmd_send(wmi, if_idx, skb, WMI_SYNCHRONIZE_CMDID,
				  NO_SYNC_WMIFLAG);

	if (ret)
		goto free_data_skb;

	for (index = 0; index < num_pri_streams; index++) {
		if (WARN_ON(!data_sync_bufs[index].skb))
			goto free_data_skb;

		ep_id = ath6kl_ac2_endpoint_id(wmi->parent_dev,
					       data_sync_bufs[index].
					       traffic_class);
		ret =
		    ath6kl_wmi_data_sync_send(wmi, data_sync_bufs[index].skb,
					      ep_id, if_idx);

		data_sync_bufs[index].skb = NULL;

		if (ret)
			goto free_data_skb;
	}

	return 0;

free_cmd_skb:
	/* free up any resources left over (possibly due to an error) */
	dev_kfree_skb(skb);

free_data_skb:
	for (index = 0; index < num_pri_streams; index++)
		dev_kfree_skb((struct sk_buff *)data_sync_bufs[index].skb);

	return ret;
}