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
typedef  int u16 ;
struct TYPE_2__ {int* buff; size_t qtail; } ;
struct ks_wlan_private {TYPE_1__ hostt; int /*<<< orphan*/  confirm_wait; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
#define  HIF_ADH_SET2_CONF 147 
#define  HIF_ADH_SET_CONF 146 
#define  HIF_AP_SET_CONF 145 
#define  HIF_ASSOC_INFO_IND 144 
#define  HIF_CONNECT_IND 143 
#define  HIF_DATA_IND 142 
#define  HIF_INFRA_SET2_CONF 141 
#define  HIF_INFRA_SET_CONF 140 
#define  HIF_MIB_GET_CONF 139 
#define  HIF_MIB_SET_CONF 138 
#define  HIF_MIC_FAILURE_CONF 137 
#define  HIF_PHY_INFO_CONF 136 
#define  HIF_PHY_INFO_IND 135 
#define  HIF_POWER_MGMT_CONF 134 
#define  HIF_PS_ADH_SET_CONF 133 
#define  HIF_SCAN_CONF 132 
#define  HIF_SCAN_IND 131 
#define  HIF_SLEEP_CONF 130 
#define  HIF_START_CONF 129 
#define  HIF_STOP_CONF 128 
 int SME_EVENT_BUFF_SIZE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int get_word (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_adhoc_set_confirm (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_associate_indication (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_bss_scan_confirm (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_connect_indication (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_data_indication (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_infrastructure_set_confirm (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_mib_get_confirm (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_mib_set_confirm (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_mic_failure_confirm (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_phy_information_confirm (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_power_mgmt_confirm (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_ps_adhoc_set_confirm (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_scan_indication (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_sleep_confirm (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_start_confirm (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_stop_confirm (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static
void hostif_event_check(struct ks_wlan_private *priv)
{
	u16 event;

	event = get_word(priv);
	switch (event) {
	case HIF_DATA_IND:
		hostif_data_indication(priv);
		break;
	case HIF_MIB_GET_CONF:
		hostif_mib_get_confirm(priv);
		break;
	case HIF_MIB_SET_CONF:
		hostif_mib_set_confirm(priv);
		break;
	case HIF_POWER_MGMT_CONF:
		hostif_power_mgmt_confirm(priv);
		break;
	case HIF_SLEEP_CONF:
		hostif_sleep_confirm(priv);
		break;
	case HIF_START_CONF:
		hostif_start_confirm(priv);
		break;
	case HIF_CONNECT_IND:
		hostif_connect_indication(priv);
		break;
	case HIF_STOP_CONF:
		hostif_stop_confirm(priv);
		break;
	case HIF_PS_ADH_SET_CONF:
		hostif_ps_adhoc_set_confirm(priv);
		break;
	case HIF_INFRA_SET_CONF:
	case HIF_INFRA_SET2_CONF:
		hostif_infrastructure_set_confirm(priv);
		break;
	case HIF_ADH_SET_CONF:
	case HIF_ADH_SET2_CONF:
		hostif_adhoc_set_confirm(priv);
		break;
	case HIF_ASSOC_INFO_IND:
		hostif_associate_indication(priv);
		break;
	case HIF_MIC_FAILURE_CONF:
		hostif_mic_failure_confirm(priv);
		break;
	case HIF_SCAN_CONF:
		hostif_bss_scan_confirm(priv);
		break;
	case HIF_PHY_INFO_CONF:
	case HIF_PHY_INFO_IND:
		hostif_phy_information_confirm(priv);
		break;
	case HIF_SCAN_IND:
		hostif_scan_indication(priv);
		break;
	case HIF_AP_SET_CONF:
	default:
		netdev_err(priv->net_dev, "undefined event[%04X]\n", event);
		/* wake_up_all(&priv->confirm_wait); */
		complete(&priv->confirm_wait);
		break;
	}

	/* add event to hostt buffer */
	priv->hostt.buff[priv->hostt.qtail] = event;
	priv->hostt.qtail = (priv->hostt.qtail + 1) % SME_EVENT_BUFF_SIZE;
}