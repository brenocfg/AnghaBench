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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wilc_vif {int /*<<< orphan*/  ndev; scalar_t__ connecting; struct host_if_drv* hif_drv; } ;
struct wid {scalar_t__* val; int size; void* type; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {void (* scan_result ) (int,struct wilc_rcvd_net_info*,void*) ;void* arg; scalar_t__ ch_cnt; } ;
struct host_if_drv {scalar_t__ hif_state; int /*<<< orphan*/  scan_timer; struct wilc_vif* scan_timer_vif; TYPE_2__ usr_scan_req; } ;
struct cfg80211_scan_request {int n_ssids; int ie_len; scalar_t__ duration; scalar_t__ ie; TYPE_1__* ssids; } ;
typedef  scalar_t__ s8 ;
typedef  int s32 ;
struct TYPE_3__ {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HOST_IF_CONNECTED ; 
 scalar_t__ HOST_IF_SCANNING ; 
 void* WID_BIN_DATA ; 
 void* WID_CHAR ; 
 int /*<<< orphan*/  WID_INFO_ELEMENT_PROBE ; 
 int /*<<< orphan*/  WID_PASSIVE_SCAN_TIME ; 
 int /*<<< orphan*/  WID_SCAN_CHANNEL_LIST ; 
 int /*<<< orphan*/  WID_SCAN_TYPE ; 
 void* WID_SHORT ; 
 int /*<<< orphan*/  WID_SSID_PROBE_REQ ; 
 int /*<<< orphan*/  WID_START_SCAN_REQ ; 
 void* WID_STR ; 
 scalar_t__ WILC_FW_PASSIVE_SCAN ; 
 size_t WILC_HIF_SCAN_TIMEOUT_MS ; 
 int /*<<< orphan*/  WILC_SET_CFG ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (size_t) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,size_t) ; 

int wilc_scan(struct wilc_vif *vif, u8 scan_source, u8 scan_type,
	      u8 *ch_freq_list, u8 ch_list_len,
	      void (*scan_result_fn)(enum scan_event,
				     struct wilc_rcvd_net_info *, void *),
	      void *user_arg, struct cfg80211_scan_request *request)
{
	int result = 0;
	struct wid wid_list[5];
	u32 index = 0;
	u32 i, scan_timeout;
	u8 *buffer;
	u8 valuesize = 0;
	u8 *search_ssid_vals = NULL;
	struct host_if_drv *hif_drv = vif->hif_drv;

	if (hif_drv->hif_state >= HOST_IF_SCANNING &&
	    hif_drv->hif_state < HOST_IF_CONNECTED) {
		netdev_err(vif->ndev, "Already scan\n");
		result = -EBUSY;
		goto error;
	}

	if (vif->connecting) {
		netdev_err(vif->ndev, "Don't do obss scan\n");
		result = -EBUSY;
		goto error;
	}

	hif_drv->usr_scan_req.ch_cnt = 0;

	if (request->n_ssids) {
		for (i = 0; i < request->n_ssids; i++)
			valuesize += ((request->ssids[i].ssid_len) + 1);
		search_ssid_vals = kmalloc(valuesize + 1, GFP_KERNEL);
		if (search_ssid_vals) {
			wid_list[index].id = WID_SSID_PROBE_REQ;
			wid_list[index].type = WID_STR;
			wid_list[index].val = search_ssid_vals;
			buffer = wid_list[index].val;

			*buffer++ = request->n_ssids;

			for (i = 0; i < request->n_ssids; i++) {
				*buffer++ = request->ssids[i].ssid_len;
				memcpy(buffer, request->ssids[i].ssid,
				       request->ssids[i].ssid_len);
				buffer += request->ssids[i].ssid_len;
			}
			wid_list[index].size = (s32)(valuesize + 1);
			index++;
		}
	}

	wid_list[index].id = WID_INFO_ELEMENT_PROBE;
	wid_list[index].type = WID_BIN_DATA;
	wid_list[index].val = (s8 *)request->ie;
	wid_list[index].size = request->ie_len;
	index++;

	wid_list[index].id = WID_SCAN_TYPE;
	wid_list[index].type = WID_CHAR;
	wid_list[index].size = sizeof(char);
	wid_list[index].val = (s8 *)&scan_type;
	index++;

	if (scan_type == WILC_FW_PASSIVE_SCAN && request->duration) {
		wid_list[index].id = WID_PASSIVE_SCAN_TIME;
		wid_list[index].type = WID_SHORT;
		wid_list[index].size = sizeof(u16);
		wid_list[index].val = (s8 *)&request->duration;
		index++;

		scan_timeout = (request->duration * ch_list_len) + 500;
	} else {
		scan_timeout = WILC_HIF_SCAN_TIMEOUT_MS;
	}

	wid_list[index].id = WID_SCAN_CHANNEL_LIST;
	wid_list[index].type = WID_BIN_DATA;

	if (ch_freq_list && ch_list_len > 0) {
		for (i = 0; i < ch_list_len; i++) {
			if (ch_freq_list[i] > 0)
				ch_freq_list[i] -= 1;
		}
	}

	wid_list[index].val = ch_freq_list;
	wid_list[index].size = ch_list_len;
	index++;

	wid_list[index].id = WID_START_SCAN_REQ;
	wid_list[index].type = WID_CHAR;
	wid_list[index].size = sizeof(char);
	wid_list[index].val = (s8 *)&scan_source;
	index++;

	hif_drv->usr_scan_req.scan_result = scan_result_fn;
	hif_drv->usr_scan_req.arg = user_arg;

	result = wilc_send_config_pkt(vif, WILC_SET_CFG, wid_list, index);
	if (result) {
		netdev_err(vif->ndev, "Failed to send scan parameters\n");
		goto error;
	}

	hif_drv->scan_timer_vif = vif;
	mod_timer(&hif_drv->scan_timer,
		  jiffies + msecs_to_jiffies(scan_timeout));

error:

	kfree(search_ssid_vals);

	return result;
}