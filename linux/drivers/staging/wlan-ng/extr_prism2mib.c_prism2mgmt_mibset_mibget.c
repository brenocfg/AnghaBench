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
typedef  int u16 ;
struct wlandevice {struct hfa384x* priv; } ;
struct TYPE_4__ {void* status; scalar_t__ data; } ;
struct TYPE_3__ {scalar_t__ data; void* status; } ;
struct p80211msg_dot11req_mibset {scalar_t__ msgcode; TYPE_2__ mibattribute; TYPE_1__ resultcode; } ;
struct p80211itemd {scalar_t__ did; void* status; scalar_t__ data; } ;
struct mibrec {scalar_t__ did; int flag; int (* func ) (struct mibrec*,int,struct wlandevice*,struct hfa384x*,struct p80211msg_dot11req_mibset*,void*) ;} ;
struct hfa384x {int dummy; } ;

/* Variables and functions */
 scalar_t__ DIDMSG_DOT11REQ_MIBGET ; 
 int F_READ ; 
 int F_STA ; 
 int F_WRITE ; 
 void* P80211ENUM_msgitem_status_data_ok ; 
 scalar_t__ P80211ENUM_resultcode_cant_get_writeonly_mib ; 
 scalar_t__ P80211ENUM_resultcode_cant_set_readonly_mib ; 
 scalar_t__ P80211ENUM_resultcode_implementation_failure ; 
 scalar_t__ P80211ENUM_resultcode_not_supported ; 
 scalar_t__ P80211ENUM_resultcode_success ; 
 struct mibrec* mibtab ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int stub1 (struct mibrec*,int,struct wlandevice*,struct hfa384x*,struct p80211msg_dot11req_mibset*,void*) ; 

int prism2mgmt_mibset_mibget(struct wlandevice *wlandev, void *msgp)
{
	struct hfa384x *hw = wlandev->priv;
	int result, isget;
	struct mibrec *mib;

	u16 which;

	struct p80211msg_dot11req_mibset *msg = msgp;
	struct p80211itemd *mibitem;

	msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
	msg->resultcode.data = P80211ENUM_resultcode_success;

	/*
	 ** Determine if this is an Access Point or a station.
	 */

	which = F_STA;

	/*
	 ** Find the MIB in the MIB table.  Note that a MIB may be in the
	 ** table twice...once for an AP and once for a station.  Make sure
	 ** to get the correct one.  Note that DID=0 marks the end of the
	 ** MIB table.
	 */

	mibitem = (struct p80211itemd *)msg->mibattribute.data;

	for (mib = mibtab; mib->did != 0; mib++)
		if (mib->did == mibitem->did && (mib->flag & which))
			break;

	if (mib->did == 0) {
		msg->resultcode.data = P80211ENUM_resultcode_not_supported;
		goto done;
	}

	/*
	 ** Determine if this is a "mibget" or a "mibset".  If this is a
	 ** "mibget", then make sure that the MIB may be read.  Otherwise,
	 ** this is a "mibset" so make make sure that the MIB may be written.
	 */

	isget = (msg->msgcode == DIDMSG_DOT11REQ_MIBGET);

	if (isget) {
		if (!(mib->flag & F_READ)) {
			msg->resultcode.data =
			    P80211ENUM_resultcode_cant_get_writeonly_mib;
			goto done;
		}
	} else {
		if (!(mib->flag & F_WRITE)) {
			msg->resultcode.data =
			    P80211ENUM_resultcode_cant_set_readonly_mib;
			goto done;
		}
	}

	/*
	 ** Execute the MIB function.  If things worked okay, then make
	 ** sure that the MIB function also worked okay.  If so, and this
	 ** is a "mibget", then the status value must be set for both the
	 ** "mibattribute" parameter and the mib item within the data
	 ** portion of the "mibattribute".
	 */

	result = mib->func(mib, isget, wlandev, hw, msg, (void *)mibitem->data);

	if (msg->resultcode.data == P80211ENUM_resultcode_success) {
		if (result != 0) {
			pr_debug("get/set failure, result=%d\n", result);
			msg->resultcode.data =
			    P80211ENUM_resultcode_implementation_failure;
		} else {
			if (isget) {
				msg->mibattribute.status =
				    P80211ENUM_msgitem_status_data_ok;
				mibitem->status =
				    P80211ENUM_msgitem_status_data_ok;
			}
		}
	}

done:
	return 0;
}