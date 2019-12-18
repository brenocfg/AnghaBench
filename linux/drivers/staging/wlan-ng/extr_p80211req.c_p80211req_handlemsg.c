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
struct wlandevice {int hostwep; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct p80211msg_lnxreq_hostwep {TYPE_1__ encrypt; TYPE_2__ decrypt; } ;
struct p80211msg_dot11req_mibget {int dummy; } ;
struct p80211msg {int msgcode; } ;

/* Variables and functions */
#define  DIDMSG_DOT11REQ_MIBGET 130 
#define  DIDMSG_DOT11REQ_MIBSET 129 
#define  DIDMSG_LNXREQ_HOSTWEP 128 
 int HOSTWEP_DECRYPT ; 
 int HOSTWEP_ENCRYPT ; 
 int /*<<< orphan*/  P80211ENUM_truth_true ; 
 int /*<<< orphan*/  p80211req_mibset_mibget (struct wlandevice*,struct p80211msg_dot11req_mibget*,int) ; 

__attribute__((used)) static void p80211req_handlemsg(struct wlandevice *wlandev,
				struct p80211msg *msg)
{
	switch (msg->msgcode) {
	case DIDMSG_LNXREQ_HOSTWEP: {
		struct p80211msg_lnxreq_hostwep *req =
			(struct p80211msg_lnxreq_hostwep *)msg;
		wlandev->hostwep &=
				~(HOSTWEP_DECRYPT | HOSTWEP_ENCRYPT);
		if (req->decrypt.data == P80211ENUM_truth_true)
			wlandev->hostwep |= HOSTWEP_DECRYPT;
		if (req->encrypt.data == P80211ENUM_truth_true)
			wlandev->hostwep |= HOSTWEP_ENCRYPT;

		break;
	}
	case DIDMSG_DOT11REQ_MIBGET:
	case DIDMSG_DOT11REQ_MIBSET: {
		int isget = (msg->msgcode == DIDMSG_DOT11REQ_MIBGET);
		struct p80211msg_dot11req_mibget *mib_msg =
			(struct p80211msg_dot11req_mibget *)msg;
		p80211req_mibset_mibget(wlandev, mib_msg, isget);
		break;
	}
	}			/* switch msg->msgcode */
}