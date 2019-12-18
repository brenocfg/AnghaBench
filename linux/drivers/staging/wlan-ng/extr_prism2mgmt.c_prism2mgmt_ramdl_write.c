#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct wlandevice {scalar_t__ msdstate; int /*<<< orphan*/  netdev; struct hfa384x* priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; void* status; } ;
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {int data; } ;
struct TYPE_5__ {int data; } ;
struct p80211msg_p2req_ramdl_write {TYPE_4__ resultcode; TYPE_3__ data; TYPE_2__ len; TYPE_1__ addr; } ;
struct hfa384x {int dummy; } ;

/* Variables and functions */
 void* P80211ENUM_msgitem_status_data_ok ; 
 int /*<<< orphan*/  P80211ENUM_resultcode_implementation_failure ; 
 void* P80211ENUM_resultcode_invalid_parameters ; 
 int /*<<< orphan*/  P80211ENUM_resultcode_refused ; 
 int /*<<< orphan*/  P80211ENUM_resultcode_success ; 
 scalar_t__ WLAN_MSD_FWLOAD ; 
 scalar_t__ hfa384x_drvr_ramdl_write (struct hfa384x*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

int prism2mgmt_ramdl_write(struct wlandevice *wlandev, void *msgp)
{
	struct hfa384x *hw = wlandev->priv;
	struct p80211msg_p2req_ramdl_write *msg = msgp;
	u32 addr;
	u32 len;
	u8 *buf;

	if (wlandev->msdstate != WLAN_MSD_FWLOAD) {
		netdev_err(wlandev->netdev,
			   "ramdl_write(): may only be called in the fwload state.\n");
		msg->resultcode.data =
		    P80211ENUM_resultcode_implementation_failure;
		msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
		return 0;
	}

	msg->resultcode.status = P80211ENUM_msgitem_status_data_ok;
	/* first validate the length */
	if (msg->len.data > sizeof(msg->data.data)) {
		msg->resultcode.status =
		    P80211ENUM_resultcode_invalid_parameters;
		return 0;
	}
	/* call the hfa384x function to do the write */
	addr = msg->addr.data;
	len = msg->len.data;
	buf = msg->data.data;
	if (hfa384x_drvr_ramdl_write(hw, addr, buf, len))
		msg->resultcode.data = P80211ENUM_resultcode_refused;

	msg->resultcode.data = P80211ENUM_resultcode_success;

	return 0;
}