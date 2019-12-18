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
typedef  int /*<<< orphan*/  u8 ;
struct wlandevice {scalar_t__ msdstate; int /*<<< orphan*/  request_pending; int /*<<< orphan*/  (* mlmerequest ) (struct wlandevice*,struct p80211msg*) ;int /*<<< orphan*/  name; int /*<<< orphan*/  netdev; } ;
struct p80211msg {scalar_t__ msgcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 scalar_t__ DIDMSG_DOT11REQ_MIBGET ; 
 scalar_t__ DIDMSG_LNXREQ_IFSTATE ; 
 int EBUSY ; 
 int ENODEV ; 
 int EPERM ; 
 scalar_t__ WLAN_MSD_FWLOAD ; 
 scalar_t__ WLAN_MSD_HWPRESENT ; 
 scalar_t__ WLAN_MSD_RUNNING ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p80211req_handlemsg (struct wlandevice*,struct p80211msg*) ; 
 int /*<<< orphan*/  stub1 (struct wlandevice*,struct p80211msg*) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 

int p80211req_dorequest(struct wlandevice *wlandev, u8 *msgbuf)
{
	struct p80211msg *msg = (struct p80211msg *)msgbuf;

	/* Check to make sure the MSD is running */
	if (!((wlandev->msdstate == WLAN_MSD_HWPRESENT &&
	       msg->msgcode == DIDMSG_LNXREQ_IFSTATE) ||
	      wlandev->msdstate == WLAN_MSD_RUNNING ||
	      wlandev->msdstate == WLAN_MSD_FWLOAD)) {
		return -ENODEV;
	}

	/* Check Permissions */
	if (!capable(CAP_NET_ADMIN) &&
	    (msg->msgcode != DIDMSG_DOT11REQ_MIBGET)) {
		netdev_err(wlandev->netdev,
			   "%s: only dot11req_mibget allowed for non-root.\n",
			   wlandev->name);
		return -EPERM;
	}

	/* Check for busy status */
	if (test_and_set_bit(1, &wlandev->request_pending))
		return -EBUSY;

	/* Allow p80211 to look at msg and handle if desired. */
	/* So far, all p80211 msgs are immediate, no waitq/timer necessary */
	/* This may change. */
	p80211req_handlemsg(wlandev, msg);

	/* Pass it down to wlandev via wlandev->mlmerequest */
	if (wlandev->mlmerequest)
		wlandev->mlmerequest(wlandev, msg);

	clear_bit(1, &wlandev->request_pending);
	return 0;	/* if result==0, msg->status still may contain an err */
}