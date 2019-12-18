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
typedef  scalar_t__ u8 ;
struct wil6210_priv {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WIL_EDMG_BW_CONFIGURATION ; 
#define  WIL_EDMG_CHANNEL_10_SUBCHANNELS 130 
#define  WIL_EDMG_CHANNEL_11_SUBCHANNELS 129 
#define  WIL_EDMG_CHANNEL_9_SUBCHANNELS 128 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,scalar_t__) ; 
 int wil_spec2wmi_ch (int,scalar_t__*) ; 

__attribute__((used)) static int wil_get_wmi_edmg_channel(struct wil6210_priv *wil, u8 edmg_bw_config,
				    u8 edmg_channels, u8 *wmi_ch)
{
	if (!edmg_bw_config) {
		*wmi_ch = 0;
		return 0;
	} else if (edmg_bw_config == WIL_EDMG_BW_CONFIGURATION) {
		/* convert from edmg channel bitmap into edmg channel number */
		switch (edmg_channels) {
		case WIL_EDMG_CHANNEL_9_SUBCHANNELS:
			return wil_spec2wmi_ch(9, wmi_ch);
		case WIL_EDMG_CHANNEL_10_SUBCHANNELS:
			return wil_spec2wmi_ch(10, wmi_ch);
		case WIL_EDMG_CHANNEL_11_SUBCHANNELS:
			return wil_spec2wmi_ch(11, wmi_ch);
		default:
			wil_err(wil, "Unsupported edmg channel bitmap 0x%x\n",
				edmg_channels);
			return -EINVAL;
		}
	} else {
		wil_err(wil, "Unsupported EDMG BW configuration %d\n",
			edmg_bw_config);
		return -EINVAL;
	}
}