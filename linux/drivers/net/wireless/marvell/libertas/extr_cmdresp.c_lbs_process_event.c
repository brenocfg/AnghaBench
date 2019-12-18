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
typedef  int u32 ;
struct lbs_private {int /*<<< orphan*/  dev; int /*<<< orphan*/  needtowakeup; int /*<<< orphan*/  psstate; int /*<<< orphan*/  ds_awake_q; int /*<<< orphan*/  wakeup_dev_required; int /*<<< orphan*/  is_deep_sleep; int /*<<< orphan*/  (* reset_deep_sleep_wakeup ) (struct lbs_private*) ;int /*<<< orphan*/  host_sleep_q; int /*<<< orphan*/  is_host_sleep_activated; int /*<<< orphan*/  cmdpendingq; } ;
struct cmd_header {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_WAKEUP_CONFIRM ; 
#define  MACREG_INT_CODE_ADHOC_BCN_LOST 146 
#define  MACREG_INT_CODE_DEAUTHENTICATED 145 
#define  MACREG_INT_CODE_DEEP_SLEEP_AWAKE 144 
#define  MACREG_INT_CODE_DISASSOCIATED 143 
#define  MACREG_INT_CODE_HOST_AWAKE 142 
#define  MACREG_INT_CODE_INIT_DONE 141 
#define  MACREG_INT_CODE_LINK_LOST_NO_SCAN 140 
#define  MACREG_INT_CODE_LINK_SENSED 139 
#define  MACREG_INT_CODE_MAX_FAIL 138 
#define  MACREG_INT_CODE_MESH_AUTO_STARTED 137 
#define  MACREG_INT_CODE_MIB_CHANGED 136 
#define  MACREG_INT_CODE_MIC_ERR_MULTICAST 135 
#define  MACREG_INT_CODE_MIC_ERR_UNICAST 134 
#define  MACREG_INT_CODE_PS_AWAKE 133 
#define  MACREG_INT_CODE_PS_SLEEP 132 
#define  MACREG_INT_CODE_RSSI_HIGH 131 
#define  MACREG_INT_CODE_RSSI_LOW 130 
#define  MACREG_INT_CODE_SNR_HIGH 129 
#define  MACREG_INT_CODE_SNR_LOW 128 
 int /*<<< orphan*/  PS_MODE_ACTION_EXIT_PS ; 
 int /*<<< orphan*/  PS_STATE_AWAKE ; 
 int /*<<< orphan*/  PS_STATE_FULL_POWER ; 
 int /*<<< orphan*/  PS_STATE_PRE_SLEEP ; 
 int /*<<< orphan*/  lbs_cmd_async (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_header*,int) ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*) ; 
 int /*<<< orphan*/  lbs_mac_event_disconnected (struct lbs_private*,int) ; 
 int /*<<< orphan*/  lbs_ps_confirm_sleep (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_send_mic_failureevent (struct lbs_private*,int) ; 
 int /*<<< orphan*/  lbs_set_ps_mode (struct lbs_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_alert (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct lbs_private*) ; 
 int /*<<< orphan*/  stub2 (struct lbs_private*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int lbs_process_event(struct lbs_private *priv, u32 event)
{
	int ret = 0;
	struct cmd_header cmd;

	switch (event) {
	case MACREG_INT_CODE_LINK_SENSED:
		lbs_deb_cmd("EVENT: link sensed\n");
		break;

	case MACREG_INT_CODE_DEAUTHENTICATED:
		lbs_deb_cmd("EVENT: deauthenticated\n");
		lbs_mac_event_disconnected(priv, false);
		break;

	case MACREG_INT_CODE_DISASSOCIATED:
		lbs_deb_cmd("EVENT: disassociated\n");
		lbs_mac_event_disconnected(priv, false);
		break;

	case MACREG_INT_CODE_LINK_LOST_NO_SCAN:
		lbs_deb_cmd("EVENT: link lost\n");
		lbs_mac_event_disconnected(priv, true);
		break;

	case MACREG_INT_CODE_PS_SLEEP:
		lbs_deb_cmd("EVENT: ps sleep\n");

		/* handle unexpected PS SLEEP event */
		if (priv->psstate == PS_STATE_FULL_POWER) {
			lbs_deb_cmd(
			       "EVENT: in FULL POWER mode, ignoring PS_SLEEP\n");
			break;
		}
		if (!list_empty(&priv->cmdpendingq)) {
			lbs_deb_cmd("EVENT: commands in queue, do not sleep\n");
			break;
		}
		priv->psstate = PS_STATE_PRE_SLEEP;

		lbs_ps_confirm_sleep(priv);

		break;

	case MACREG_INT_CODE_HOST_AWAKE:
		lbs_deb_cmd("EVENT: host awake\n");
		if (priv->reset_deep_sleep_wakeup)
			priv->reset_deep_sleep_wakeup(priv);
		priv->is_deep_sleep = 0;
		lbs_cmd_async(priv, CMD_802_11_WAKEUP_CONFIRM, &cmd,
				sizeof(cmd));
		priv->is_host_sleep_activated = 0;
		wake_up_interruptible(&priv->host_sleep_q);
		break;

	case MACREG_INT_CODE_DEEP_SLEEP_AWAKE:
		if (priv->reset_deep_sleep_wakeup)
			priv->reset_deep_sleep_wakeup(priv);
		lbs_deb_cmd("EVENT: ds awake\n");
		priv->is_deep_sleep = 0;
		priv->wakeup_dev_required = 0;
		wake_up_interruptible(&priv->ds_awake_q);
		break;

	case MACREG_INT_CODE_PS_AWAKE:
		lbs_deb_cmd("EVENT: ps awake\n");
		/* handle unexpected PS AWAKE event */
		if (priv->psstate == PS_STATE_FULL_POWER) {
			lbs_deb_cmd(
			       "EVENT: In FULL POWER mode - ignore PS AWAKE\n");
			break;
		}

		priv->psstate = PS_STATE_AWAKE;

		if (priv->needtowakeup) {
			/*
			 * wait for the command processing to finish
			 * before resuming sending
			 * priv->needtowakeup will be set to FALSE
			 * in lbs_ps_wakeup()
			 */
			lbs_deb_cmd("waking up ...\n");
			lbs_set_ps_mode(priv, PS_MODE_ACTION_EXIT_PS, false);
		}
		break;

	case MACREG_INT_CODE_MIC_ERR_UNICAST:
		lbs_deb_cmd("EVENT: UNICAST MIC ERROR\n");
		lbs_send_mic_failureevent(priv, event);
		break;

	case MACREG_INT_CODE_MIC_ERR_MULTICAST:
		lbs_deb_cmd("EVENT: MULTICAST MIC ERROR\n");
		lbs_send_mic_failureevent(priv, event);
		break;

	case MACREG_INT_CODE_MIB_CHANGED:
		lbs_deb_cmd("EVENT: MIB CHANGED\n");
		break;
	case MACREG_INT_CODE_INIT_DONE:
		lbs_deb_cmd("EVENT: INIT DONE\n");
		break;
	case MACREG_INT_CODE_ADHOC_BCN_LOST:
		lbs_deb_cmd("EVENT: ADHOC beacon lost\n");
		break;
	case MACREG_INT_CODE_RSSI_LOW:
		netdev_alert(priv->dev, "EVENT: rssi low\n");
		break;
	case MACREG_INT_CODE_SNR_LOW:
		netdev_alert(priv->dev, "EVENT: snr low\n");
		break;
	case MACREG_INT_CODE_MAX_FAIL:
		netdev_alert(priv->dev, "EVENT: max fail\n");
		break;
	case MACREG_INT_CODE_RSSI_HIGH:
		netdev_alert(priv->dev, "EVENT: rssi high\n");
		break;
	case MACREG_INT_CODE_SNR_HIGH:
		netdev_alert(priv->dev, "EVENT: snr high\n");
		break;

	case MACREG_INT_CODE_MESH_AUTO_STARTED:
		/* Ignore spurious autostart events */
		netdev_info(priv->dev, "EVENT: MESH_AUTO_STARTED (ignoring)\n");
		break;

	default:
		netdev_alert(priv->dev, "EVENT: unknown event id %d\n", event);
		break;
	}

	return ret;
}