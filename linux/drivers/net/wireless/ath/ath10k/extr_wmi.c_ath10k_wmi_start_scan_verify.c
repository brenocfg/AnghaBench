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
struct wmi_start_scan_arg {scalar_t__ ie_len; scalar_t__ n_channels; scalar_t__ n_ssids; scalar_t__ n_bssids; int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ WLAN_SCAN_PARAMS_MAX_BSSID ; 
 scalar_t__ WLAN_SCAN_PARAMS_MAX_IE_LEN ; 
 scalar_t__ WLAN_SCAN_PARAMS_MAX_SSID ; 

int ath10k_wmi_start_scan_verify(const struct wmi_start_scan_arg *arg)
{
	if (arg->ie_len > WLAN_SCAN_PARAMS_MAX_IE_LEN)
		return -EINVAL;
	if (arg->n_channels > ARRAY_SIZE(arg->channels))
		return -EINVAL;
	if (arg->n_ssids > WLAN_SCAN_PARAMS_MAX_SSID)
		return -EINVAL;
	if (arg->n_bssids > WLAN_SCAN_PARAMS_MAX_BSSID)
		return -EINVAL;

	return 0;
}