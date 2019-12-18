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
typedef  size_t u32 ;
struct wmi_mgmt_rx_ext_info {int dummy; } ;
struct wmi_mgmt_rx_ev_arg {int /*<<< orphan*/  ext_info; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  status; int /*<<< orphan*/  rate; int /*<<< orphan*/  phy_mode; int /*<<< orphan*/  snr; int /*<<< orphan*/  channel; } ;
struct wmi_10_4_mgmt_rx_hdr {int /*<<< orphan*/  rate; int /*<<< orphan*/  phy_mode; int /*<<< orphan*/  snr; int /*<<< orphan*/  status; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  channel; } ;
struct wmi_10_4_mgmt_rx_event {struct wmi_10_4_mgmt_rx_hdr hdr; } ;
struct sk_buff {size_t data; size_t len; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 size_t ALIGN (int,int) ; 
 int EPROTO ; 
 int WMI_RX_STATUS_EXT_INFO ; 
 size_t __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct wmi_mgmt_rx_ext_info*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,size_t) ; 

__attribute__((used)) static int ath10k_wmi_10_4_op_pull_mgmt_rx_ev(struct ath10k *ar,
					      struct sk_buff *skb,
					      struct wmi_mgmt_rx_ev_arg *arg)
{
	struct wmi_10_4_mgmt_rx_event *ev;
	struct wmi_10_4_mgmt_rx_hdr *ev_hdr;
	size_t pull_len;
	u32 msdu_len;
	struct wmi_mgmt_rx_ext_info *ext_info;
	u32 len;

	ev = (struct wmi_10_4_mgmt_rx_event *)skb->data;
	ev_hdr = &ev->hdr;
	pull_len = sizeof(*ev);

	if (skb->len < pull_len)
		return -EPROTO;

	skb_pull(skb, pull_len);
	arg->channel = ev_hdr->channel;
	arg->buf_len = ev_hdr->buf_len;
	arg->status = ev_hdr->status;
	arg->snr = ev_hdr->snr;
	arg->phy_mode = ev_hdr->phy_mode;
	arg->rate = ev_hdr->rate;

	msdu_len = __le32_to_cpu(arg->buf_len);
	if (skb->len < msdu_len)
		return -EPROTO;

	if (le32_to_cpu(arg->status) & WMI_RX_STATUS_EXT_INFO) {
		len = ALIGN(le32_to_cpu(arg->buf_len), 4);
		ext_info = (struct wmi_mgmt_rx_ext_info *)(skb->data + len);
		memcpy(&arg->ext_info, ext_info,
		       sizeof(struct wmi_mgmt_rx_ext_info));
	}

	/* Make sure bytes added for padding are removed. */
	skb_trim(skb, msdu_len);

	return 0;
}