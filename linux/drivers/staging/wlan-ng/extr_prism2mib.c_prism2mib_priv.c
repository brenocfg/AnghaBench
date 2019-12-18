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
typedef  int /*<<< orphan*/  wpa ;
typedef  int /*<<< orphan*/  u8 ;
struct wlandevice {int /*<<< orphan*/  netdev; } ;
struct p80211pstrd {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct p80211msg_dot11req_mibset {int dummy; } ;
struct mibrec {int did; } ;
struct hfa384x_wpa_data {int /*<<< orphan*/  data; int /*<<< orphan*/  datalen; } ;
struct hfa384x {int dummy; } ;

/* Variables and functions */
#define  DIDMIB_LNX_CONFIGTABLE_RSNAIE 128 
 int /*<<< orphan*/  HFA384x_RID_CNFWPADATA ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfa384x_drvr_getconfig (struct hfa384x*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hfa384x_drvr_setconfig (struct hfa384x*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int prism2mib_priv(struct mibrec *mib,
			  int isget,
			  struct wlandevice *wlandev,
			  struct hfa384x *hw,
			  struct p80211msg_dot11req_mibset *msg, void *data)
{
	struct p80211pstrd *pstr = data;

	switch (mib->did) {
	case DIDMIB_LNX_CONFIGTABLE_RSNAIE: {
		struct hfa384x_wpa_data wpa;

		if (isget) {
			hfa384x_drvr_getconfig(hw,
					       HFA384x_RID_CNFWPADATA,
					       (u8 *)&wpa,
					       sizeof(wpa));
			pstr->len = le16_to_cpu(wpa.datalen);
			memcpy(pstr->data, wpa.data, pstr->len);
		} else {
			wpa.datalen = cpu_to_le16(pstr->len);
			memcpy(wpa.data, pstr->data, pstr->len);

			hfa384x_drvr_setconfig(hw,
					       HFA384x_RID_CNFWPADATA,
					       (u8 *)&wpa,
					       sizeof(wpa));
		}
		break;
	}
	default:
		netdev_err(wlandev->netdev, "Unhandled DID 0x%08x\n", mib->did);
	}

	return 0;
}