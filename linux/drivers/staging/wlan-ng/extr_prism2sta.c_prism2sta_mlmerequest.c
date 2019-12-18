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
struct wlandevice {int /*<<< orphan*/  netdev; struct hfa384x* priv; } ;
struct TYPE_9__ {int data; void* status; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct p80211msg_lnxreq_ifstate {TYPE_2__ resultcode; TYPE_1__ ifstate; } ;
struct TYPE_14__ {int /*<<< orphan*/  data; } ;
struct TYPE_12__ {void* data; void* status; } ;
struct TYPE_11__ {void* data; void* status; } ;
struct TYPE_10__ {void* data; void* status; } ;
struct p80211msg_lnxreq_commsquality {TYPE_7__ txrate; TYPE_5__ noise; TYPE_4__ level; TYPE_3__ link; } ;
struct p80211msg {int msgcode; } ;
struct TYPE_13__ {int /*<<< orphan*/  anl_curr_fc; int /*<<< orphan*/  asl_curr_bss; int /*<<< orphan*/  cq_curr_bss; } ;
struct hfa384x {int /*<<< orphan*/  txrate; TYPE_6__ qual; } ;

/* Variables and functions */
#define  DIDMSG_DOT11REQ_MIBGET 142 
#define  DIDMSG_DOT11REQ_MIBSET 141 
#define  DIDMSG_DOT11REQ_SCAN 140 
#define  DIDMSG_DOT11REQ_SCAN_RESULTS 139 
#define  DIDMSG_DOT11REQ_START 138 
#define  DIDMSG_LNXREQ_AUTOJOIN 137 
#define  DIDMSG_LNXREQ_COMMSQUALITY 136 
#define  DIDMSG_LNXREQ_HOSTWEP 135 
#define  DIDMSG_LNXREQ_IFSTATE 134 
#define  DIDMSG_LNXREQ_WLANSNIFF 133 
#define  DIDMSG_P2REQ_FLASHDL_STATE 132 
#define  DIDMSG_P2REQ_FLASHDL_WRITE 131 
#define  DIDMSG_P2REQ_RAMDL_STATE 130 
#define  DIDMSG_P2REQ_RAMDL_WRITE 129 
#define  DIDMSG_P2REQ_READPDA 128 
 void* P80211ENUM_msgitem_status_data_ok ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int prism2mgmt_autojoin (struct wlandevice*,struct p80211msg*) ; 
 int prism2mgmt_flashdl_state (struct wlandevice*,struct p80211msg*) ; 
 int prism2mgmt_flashdl_write (struct wlandevice*,struct p80211msg*) ; 
 int prism2mgmt_mibset_mibget (struct wlandevice*,struct p80211msg*) ; 
 int prism2mgmt_ramdl_state (struct wlandevice*,struct p80211msg*) ; 
 int prism2mgmt_ramdl_write (struct wlandevice*,struct p80211msg*) ; 
 int prism2mgmt_readpda (struct wlandevice*,struct p80211msg*) ; 
 int prism2mgmt_scan (struct wlandevice*,struct p80211msg*) ; 
 int prism2mgmt_scan_results (struct wlandevice*,struct p80211msg*) ; 
 int prism2mgmt_start (struct wlandevice*,struct p80211msg*) ; 
 int prism2mgmt_wlansniff (struct wlandevice*,struct p80211msg*) ; 
 int prism2sta_ifstate (struct wlandevice*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prism2sta_mlmerequest(struct wlandevice *wlandev,
				 struct p80211msg *msg)
{
	struct hfa384x *hw = wlandev->priv;

	int result = 0;

	switch (msg->msgcode) {
	case DIDMSG_DOT11REQ_MIBGET:
		pr_debug("Received mibget request\n");
		result = prism2mgmt_mibset_mibget(wlandev, msg);
		break;
	case DIDMSG_DOT11REQ_MIBSET:
		pr_debug("Received mibset request\n");
		result = prism2mgmt_mibset_mibget(wlandev, msg);
		break;
	case DIDMSG_DOT11REQ_SCAN:
		pr_debug("Received scan request\n");
		result = prism2mgmt_scan(wlandev, msg);
		break;
	case DIDMSG_DOT11REQ_SCAN_RESULTS:
		pr_debug("Received scan_results request\n");
		result = prism2mgmt_scan_results(wlandev, msg);
		break;
	case DIDMSG_DOT11REQ_START:
		pr_debug("Received mlme start request\n");
		result = prism2mgmt_start(wlandev, msg);
		break;
		/*
		 * Prism2 specific messages
		 */
	case DIDMSG_P2REQ_READPDA:
		pr_debug("Received mlme readpda request\n");
		result = prism2mgmt_readpda(wlandev, msg);
		break;
	case DIDMSG_P2REQ_RAMDL_STATE:
		pr_debug("Received mlme ramdl_state request\n");
		result = prism2mgmt_ramdl_state(wlandev, msg);
		break;
	case DIDMSG_P2REQ_RAMDL_WRITE:
		pr_debug("Received mlme ramdl_write request\n");
		result = prism2mgmt_ramdl_write(wlandev, msg);
		break;
	case DIDMSG_P2REQ_FLASHDL_STATE:
		pr_debug("Received mlme flashdl_state request\n");
		result = prism2mgmt_flashdl_state(wlandev, msg);
		break;
	case DIDMSG_P2REQ_FLASHDL_WRITE:
		pr_debug("Received mlme flashdl_write request\n");
		result = prism2mgmt_flashdl_write(wlandev, msg);
		break;
		/*
		 * Linux specific messages
		 */
	case DIDMSG_LNXREQ_HOSTWEP:
		break;		/* ignore me. */
	case DIDMSG_LNXREQ_IFSTATE: {
		struct p80211msg_lnxreq_ifstate *ifstatemsg;

		pr_debug("Received mlme ifstate request\n");
		ifstatemsg = (struct p80211msg_lnxreq_ifstate *)msg;
		result = prism2sta_ifstate(wlandev,
					   ifstatemsg->ifstate.data);
		ifstatemsg->resultcode.status =
			P80211ENUM_msgitem_status_data_ok;
		ifstatemsg->resultcode.data = result;
		result = 0;
		break;
	}
	case DIDMSG_LNXREQ_WLANSNIFF:
		pr_debug("Received mlme wlansniff request\n");
		result = prism2mgmt_wlansniff(wlandev, msg);
		break;
	case DIDMSG_LNXREQ_AUTOJOIN:
		pr_debug("Received mlme autojoin request\n");
		result = prism2mgmt_autojoin(wlandev, msg);
		break;
	case DIDMSG_LNXREQ_COMMSQUALITY: {
		struct p80211msg_lnxreq_commsquality *qualmsg;

		pr_debug("Received commsquality request\n");

		qualmsg = (struct p80211msg_lnxreq_commsquality *)msg;

		qualmsg->link.status = P80211ENUM_msgitem_status_data_ok;
		qualmsg->level.status = P80211ENUM_msgitem_status_data_ok;
		qualmsg->noise.status = P80211ENUM_msgitem_status_data_ok;

		qualmsg->link.data = le16_to_cpu(hw->qual.cq_curr_bss);
		qualmsg->level.data = le16_to_cpu(hw->qual.asl_curr_bss);
		qualmsg->noise.data = le16_to_cpu(hw->qual.anl_curr_fc);
		qualmsg->txrate.data = hw->txrate;

		break;
	}
	default:
		netdev_warn(wlandev->netdev,
			    "Unknown mgmt request message 0x%08x",
			    msg->msgcode);
		break;
	}

	return result;
}