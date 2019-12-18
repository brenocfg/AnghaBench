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
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ath10k {TYPE_2__* running_fw; } ;
struct TYPE_3__ {int /*<<< orphan*/  fw_features; } ;
struct TYPE_4__ {TYPE_1__ fw_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FW_FEATURE_NO_NWIFI_DECAP_4ADDR_PADDING ; 
 int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int round_up (int,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_htt_rx_nwifi_hdrlen(struct ath10k *ar,
				      struct ieee80211_hdr *hdr)
{
	int len = ieee80211_hdrlen(hdr->frame_control);

	if (!test_bit(ATH10K_FW_FEATURE_NO_NWIFI_DECAP_4ADDR_PADDING,
		      ar->running_fw->fw_file.fw_features))
		len = round_up(len, 4);

	return len;
}