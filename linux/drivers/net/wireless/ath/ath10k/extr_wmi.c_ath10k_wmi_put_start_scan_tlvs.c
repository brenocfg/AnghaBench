#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wmi_start_scan_tlvs {void* tlvs; } ;
struct wmi_start_scan_arg {int n_channels; int n_ssids; int n_bssids; int ie_len; int /*<<< orphan*/  ie; TYPE_5__* bssids; TYPE_3__* ssids; int /*<<< orphan*/ * channels; } ;
struct wmi_ssid_list {TYPE_2__* ssids; void* num_ssids; void* tag; } ;
struct wmi_ssid {int dummy; } ;
struct wmi_mac_addr {int dummy; } ;
struct wmi_ie_data {int /*<<< orphan*/ * ie_data; void* ie_len; void* tag; } ;
struct wmi_chan_list {TYPE_1__* channel_list; void* num_chan; void* tag; } ;
struct wmi_bssid_list {TYPE_4__* bssid_list; void* num_bssid; void* tag; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_10__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {int len; int /*<<< orphan*/  ssid; } ;
struct TYPE_7__ {int /*<<< orphan*/  ssid; void* ssid_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int WMI_BSSID_LIST_TAG ; 
 int WMI_CHAN_LIST_TAG ; 
 int WMI_IE_TAG ; 
 int WMI_SSID_LIST_TAG ; 
 int /*<<< orphan*/  __cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* __cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roundup (int,int) ; 

__attribute__((used)) static void
ath10k_wmi_put_start_scan_tlvs(struct wmi_start_scan_tlvs *tlvs,
			       const struct wmi_start_scan_arg *arg)
{
	struct wmi_ie_data *ie;
	struct wmi_chan_list *channels;
	struct wmi_ssid_list *ssids;
	struct wmi_bssid_list *bssids;
	void *ptr = tlvs->tlvs;
	int i;

	if (arg->n_channels) {
		channels = ptr;
		channels->tag = __cpu_to_le32(WMI_CHAN_LIST_TAG);
		channels->num_chan = __cpu_to_le32(arg->n_channels);

		for (i = 0; i < arg->n_channels; i++)
			channels->channel_list[i].freq =
				__cpu_to_le16(arg->channels[i]);

		ptr += sizeof(*channels);
		ptr += sizeof(__le32) * arg->n_channels;
	}

	if (arg->n_ssids) {
		ssids = ptr;
		ssids->tag = __cpu_to_le32(WMI_SSID_LIST_TAG);
		ssids->num_ssids = __cpu_to_le32(arg->n_ssids);

		for (i = 0; i < arg->n_ssids; i++) {
			ssids->ssids[i].ssid_len =
				__cpu_to_le32(arg->ssids[i].len);
			memcpy(&ssids->ssids[i].ssid,
			       arg->ssids[i].ssid,
			       arg->ssids[i].len);
		}

		ptr += sizeof(*ssids);
		ptr += sizeof(struct wmi_ssid) * arg->n_ssids;
	}

	if (arg->n_bssids) {
		bssids = ptr;
		bssids->tag = __cpu_to_le32(WMI_BSSID_LIST_TAG);
		bssids->num_bssid = __cpu_to_le32(arg->n_bssids);

		for (i = 0; i < arg->n_bssids; i++)
			ether_addr_copy(bssids->bssid_list[i].addr,
					arg->bssids[i].bssid);

		ptr += sizeof(*bssids);
		ptr += sizeof(struct wmi_mac_addr) * arg->n_bssids;
	}

	if (arg->ie_len) {
		ie = ptr;
		ie->tag = __cpu_to_le32(WMI_IE_TAG);
		ie->ie_len = __cpu_to_le32(arg->ie_len);
		memcpy(ie->ie_data, arg->ie, arg->ie_len);

		ptr += sizeof(*ie);
		ptr += roundup(arg->ie_len, 4);
	}
}