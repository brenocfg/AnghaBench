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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct wmi_rx_action_event {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; int /*<<< orphan*/  freq; } ;
struct wmi {int dummy; } ;
struct ath6kl_vif {int /*<<< orphan*/  wdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int EINVAL ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_err (char*,int,int) ; 
 int /*<<< orphan*/  cfg80211_rx_mgmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_wmi_rx_action_event_rx(struct wmi *wmi, u8 *datap, int len,
					 struct ath6kl_vif *vif)
{
	struct wmi_rx_action_event *ev;
	u32 freq;
	u16 dlen;

	if (len < sizeof(*ev))
		return -EINVAL;

	ev = (struct wmi_rx_action_event *) datap;
	freq = le32_to_cpu(ev->freq);
	dlen = le16_to_cpu(ev->len);
	if (datap + len < ev->data + dlen) {
		ath6kl_err("invalid wmi_rx_action_event: len=%d dlen=%u\n",
			   len, dlen);
		return -EINVAL;
	}
	ath6kl_dbg(ATH6KL_DBG_WMI, "rx_action: len=%u freq=%u\n", dlen, freq);
	cfg80211_rx_mgmt(&vif->wdev, freq, 0, ev->data, dlen, 0);

	return 0;
}