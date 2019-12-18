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
typedef  int /*<<< orphan*/  u32 ;
struct wmi_vdev_start_ev_arg {int /*<<< orphan*/  status; } ;
struct sk_buff {int dummy; } ;
struct ath10k {int last_wmi_vdev_start_status; int /*<<< orphan*/  vdev_setup_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int EINVAL ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMI_VDEV_START_CHAN_INVALID ; 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int,...) ; 
 int ath10k_wmi_pull_vdev_start (struct ath10k*,struct sk_buff*,struct wmi_vdev_start_ev_arg*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

void ath10k_wmi_event_vdev_start_resp(struct ath10k *ar, struct sk_buff *skb)
{
	struct wmi_vdev_start_ev_arg arg = {};
	int ret;
	u32 status;

	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_VDEV_START_RESP_EVENTID\n");

	ar->last_wmi_vdev_start_status = 0;

	ret = ath10k_wmi_pull_vdev_start(ar, skb, &arg);
	if (ret) {
		ath10k_warn(ar, "failed to parse vdev start event: %d\n", ret);
		ar->last_wmi_vdev_start_status = ret;
		goto out;
	}

	status = __le32_to_cpu(arg.status);
	if (WARN_ON_ONCE(status)) {
		ath10k_warn(ar, "vdev-start-response reports status error: %d (%s)\n",
			    status, (status == WMI_VDEV_START_CHAN_INVALID) ?
			    "chan-invalid" : "unknown");
		/* Setup is done one way or another though, so we should still
		 * do the completion, so don't return here.
		 */
		ar->last_wmi_vdev_start_status = -EINVAL;
	}

out:
	complete(&ar->vdev_setup_done);
}