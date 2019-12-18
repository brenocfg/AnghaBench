#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wlandevice {int /*<<< orphan*/  netdev; struct hfa384x* priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  algorithm; int /*<<< orphan*/ * sta_addr; } ;
struct TYPE_9__ {TYPE_3__ authreq; } ;
struct hfa384x_inf_frame {TYPE_4__ info; } ;
struct hfa384x_authenticate_station_data {scalar_t__ status; int /*<<< orphan*/  algorithm; int /*<<< orphan*/ * address; } ;
struct TYPE_10__ {int cnt; int /*<<< orphan*/ ** addr; } ;
struct TYPE_7__ {int cnt; int cnt1; int /*<<< orphan*/ ** addr1; int /*<<< orphan*/ ** addr; int /*<<< orphan*/  modify; } ;
struct TYPE_6__ {int cnt; int cnt1; int /*<<< orphan*/ ** addr1; int /*<<< orphan*/ ** addr; int /*<<< orphan*/  modify; } ;
struct hfa384x {int accessmode; TYPE_5__ authlist; TYPE_2__ deny; TYPE_1__ allow; } ;
typedef  int /*<<< orphan*/  rec ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HFA384x_RID_AUTHENTICATESTA ; 
 int /*<<< orphan*/  P80211ENUM_status_ap_full ; 
 int /*<<< orphan*/  P80211ENUM_status_successful ; 
 int /*<<< orphan*/  P80211ENUM_status_unspec_failure ; 
#define  WLAN_ACCESS_ALL 131 
#define  WLAN_ACCESS_ALLOW 130 
#define  WLAN_ACCESS_DENY 129 
#define  WLAN_ACCESS_NONE 128 
 int WLAN_AUTH_MAX ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hfa384x_drvr_setconfig (struct hfa384x*,int /*<<< orphan*/ ,struct hfa384x_authenticate_station_data*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void prism2sta_inf_authreq_defer(struct wlandevice *wlandev,
					struct hfa384x_inf_frame *inf)
{
	struct hfa384x *hw = wlandev->priv;
	struct hfa384x_authenticate_station_data rec;

	int i, added, result, cnt;
	u8 *addr;

	/*
	 * Build the AuthenticateStation record.  Initialize it for denying
	 * authentication.
	 */

	ether_addr_copy(rec.address, inf->info.authreq.sta_addr);
	rec.status = cpu_to_le16(P80211ENUM_status_unspec_failure);

	/*
	 * Authenticate based on the access mode.
	 */

	switch (hw->accessmode) {
	case WLAN_ACCESS_NONE:

		/*
		 * Deny all new authentications.  However, if a station
		 * is ALREADY authenticated, then accept it.
		 */

		for (i = 0; i < hw->authlist.cnt; i++)
			if (ether_addr_equal(rec.address,
					     hw->authlist.addr[i])) {
				rec.status = cpu_to_le16(P80211ENUM_status_successful);
				break;
			}

		break;

	case WLAN_ACCESS_ALL:

		/*
		 * Allow all authentications.
		 */

		rec.status = cpu_to_le16(P80211ENUM_status_successful);
		break;

	case WLAN_ACCESS_ALLOW:

		/*
		 * Only allow the authentication if the MAC address
		 * is in the list of allowed addresses.
		 *
		 * Since this is the interrupt handler, we may be here
		 * while the access list is in the middle of being
		 * updated.  Choose the list which is currently okay.
		 * See "prism2mib_priv_accessallow()" for details.
		 */

		if (hw->allow.modify == 0) {
			cnt = hw->allow.cnt;
			addr = hw->allow.addr[0];
		} else {
			cnt = hw->allow.cnt1;
			addr = hw->allow.addr1[0];
		}

		for (i = 0; i < cnt; i++, addr += ETH_ALEN)
			if (ether_addr_equal(rec.address, addr)) {
				rec.status = cpu_to_le16(P80211ENUM_status_successful);
				break;
			}

		break;

	case WLAN_ACCESS_DENY:

		/*
		 * Allow the authentication UNLESS the MAC address is
		 * in the list of denied addresses.
		 *
		 * Since this is the interrupt handler, we may be here
		 * while the access list is in the middle of being
		 * updated.  Choose the list which is currently okay.
		 * See "prism2mib_priv_accessdeny()" for details.
		 */

		if (hw->deny.modify == 0) {
			cnt = hw->deny.cnt;
			addr = hw->deny.addr[0];
		} else {
			cnt = hw->deny.cnt1;
			addr = hw->deny.addr1[0];
		}

		rec.status = cpu_to_le16(P80211ENUM_status_successful);

		for (i = 0; i < cnt; i++, addr += ETH_ALEN)
			if (ether_addr_equal(rec.address, addr)) {
				rec.status = cpu_to_le16(P80211ENUM_status_unspec_failure);
				break;
			}

		break;
	}

	/*
	 * If the authentication is okay, then add the MAC address to the
	 * list of authenticated stations.  Don't add the address if it
	 * is already in the list. (802.11b does not seem to disallow
	 * a station from issuing an authentication request when the
	 * station is already authenticated. Does this sort of thing
	 * ever happen?  We might as well do the check just in case.)
	 */

	added = 0;

	if (rec.status == cpu_to_le16(P80211ENUM_status_successful)) {
		for (i = 0; i < hw->authlist.cnt; i++)
			if (ether_addr_equal(rec.address,
					     hw->authlist.addr[i]))
				break;

		if (i >= hw->authlist.cnt) {
			if (hw->authlist.cnt >= WLAN_AUTH_MAX) {
				rec.status = cpu_to_le16(P80211ENUM_status_ap_full);
			} else {
				ether_addr_copy(hw->authlist.addr[hw->authlist.cnt],
						rec.address);
				hw->authlist.cnt++;
				added = 1;
			}
		}
	}

	/*
	 * Send back the results of the authentication.  If this doesn't work,
	 * then make sure to remove the address from the authenticated list if
	 * it was added.
	 */

	rec.algorithm = inf->info.authreq.algorithm;

	result = hfa384x_drvr_setconfig(hw, HFA384x_RID_AUTHENTICATESTA,
					&rec, sizeof(rec));
	if (result) {
		if (added)
			hw->authlist.cnt--;
		netdev_err(wlandev->netdev,
			   "setconfig(authenticatestation) failed, result=%d\n",
			   result);
	}
}