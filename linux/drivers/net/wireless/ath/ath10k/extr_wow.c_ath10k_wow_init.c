#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  n_patterns; int /*<<< orphan*/  max_nd_match_sets; int /*<<< orphan*/  flags; int /*<<< orphan*/  max_pkt_offset; int /*<<< orphan*/  pattern_max_len; } ;
struct TYPE_13__ {TYPE_7__ wowlan_support; int /*<<< orphan*/  max_num_patterns; } ;
struct TYPE_10__ {scalar_t__ rx_decap_mode; int /*<<< orphan*/  svc_map; } ;
struct ath10k {int /*<<< orphan*/  dev; TYPE_6__ wow; TYPE_5__* hw; TYPE_3__ wmi; TYPE_2__* running_fw; } ;
struct TYPE_12__ {TYPE_4__* wiphy; } ;
struct TYPE_11__ {TYPE_7__* wowlan; } ;
struct TYPE_8__ {int /*<<< orphan*/  fw_features; } ;
struct TYPE_9__ {TYPE_1__ fw_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FW_FEATURE_WOWLAN_SUPPORT ; 
 scalar_t__ ATH10K_HW_TXRX_NATIVE_WIFI ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WIPHY_WOWLAN_NET_DETECT ; 
 int /*<<< orphan*/  WMI_PNO_MAX_SUPP_NETWORKS ; 
 int /*<<< orphan*/  WMI_SERVICE_NLO ; 
 int /*<<< orphan*/  WMI_SERVICE_WOW ; 
 scalar_t__ WOW_MAX_REDUCE ; 
 TYPE_7__ ath10k_wowlan_support ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ath10k_wow_init(struct ath10k *ar)
{
	if (!test_bit(ATH10K_FW_FEATURE_WOWLAN_SUPPORT,
		      ar->running_fw->fw_file.fw_features))
		return 0;

	if (WARN_ON(!test_bit(WMI_SERVICE_WOW, ar->wmi.svc_map)))
		return -EINVAL;

	ar->wow.wowlan_support = ath10k_wowlan_support;

	if (ar->wmi.rx_decap_mode == ATH10K_HW_TXRX_NATIVE_WIFI) {
		ar->wow.wowlan_support.pattern_max_len -= WOW_MAX_REDUCE;
		ar->wow.wowlan_support.max_pkt_offset -= WOW_MAX_REDUCE;
	}

	if (test_bit(WMI_SERVICE_NLO, ar->wmi.svc_map)) {
		ar->wow.wowlan_support.flags |= WIPHY_WOWLAN_NET_DETECT;
		ar->wow.wowlan_support.max_nd_match_sets = WMI_PNO_MAX_SUPP_NETWORKS;
	}

	ar->wow.wowlan_support.n_patterns = ar->wow.max_num_patterns;
	ar->hw->wiphy->wowlan = &ar->wow.wowlan_support;

	device_set_wakeup_capable(ar->dev, true);

	return 0;
}