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
struct wmi_start_scan_arg {int scan_req_id; int dwell_time_active; int dwell_time_passive; int min_rest_time; int max_rest_time; int max_scan_time; int probe_delay; int notify_scan_events; int n_bssids; TYPE_1__* bssids; int /*<<< orphan*/  scan_ctrl_flags; scalar_t__ idle_time; scalar_t__ probe_spacing_time; scalar_t__ repeat_probe_time; int /*<<< orphan*/  scan_priority; } ;
struct ath10k {int dummy; } ;
struct TYPE_2__ {char* bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_SCAN_CHAN_STAT_EVENT ; 
 int WMI_SCAN_EVENT_BSS_CHANNEL ; 
 int WMI_SCAN_EVENT_COMPLETED ; 
 int WMI_SCAN_EVENT_DEQUEUED ; 
 int WMI_SCAN_EVENT_FOREIGN_CHANNEL ; 
 int WMI_SCAN_EVENT_FOREIGN_CHANNEL_EXIT ; 
 int WMI_SCAN_EVENT_STARTED ; 
 int /*<<< orphan*/  WMI_SCAN_PRIORITY_LOW ; 

void ath10k_wmi_start_scan_init(struct ath10k *ar,
				struct wmi_start_scan_arg *arg)
{
	/* setup commonly used values */
	arg->scan_req_id = 1;
	arg->scan_priority = WMI_SCAN_PRIORITY_LOW;
	arg->dwell_time_active = 50;
	arg->dwell_time_passive = 150;
	arg->min_rest_time = 50;
	arg->max_rest_time = 500;
	arg->repeat_probe_time = 0;
	arg->probe_spacing_time = 0;
	arg->idle_time = 0;
	arg->max_scan_time = 20000;
	arg->probe_delay = 5;
	arg->notify_scan_events = WMI_SCAN_EVENT_STARTED
		| WMI_SCAN_EVENT_COMPLETED
		| WMI_SCAN_EVENT_BSS_CHANNEL
		| WMI_SCAN_EVENT_FOREIGN_CHANNEL
		| WMI_SCAN_EVENT_FOREIGN_CHANNEL_EXIT
		| WMI_SCAN_EVENT_DEQUEUED;
	arg->scan_ctrl_flags |= WMI_SCAN_CHAN_STAT_EVENT;
	arg->n_bssids = 1;
	arg->bssids[0].bssid = "\xFF\xFF\xFF\xFF\xFF\xFF";
}