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
typedef  int /*<<< orphan*/  u8 ;
struct wlandevice {int /*<<< orphan*/  name; } ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct p80211item_uint32 {int len; scalar_t__ data; int /*<<< orphan*/  status; int /*<<< orphan*/  did; } ;
struct p80211item_unk392 {int len; void* status; int /*<<< orphan*/  did; int /*<<< orphan*/  data; } ;
struct p80211msg_dot11req_mibset {int msglen; int /*<<< orphan*/ * devname; int /*<<< orphan*/  msgcode; struct p80211item_uint32 resultcode; struct p80211item_unk392 mibattribute; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; scalar_t__ len; } ;
struct p80211item_pstr6 {int len; TYPE_1__ data; void* status; int /*<<< orphan*/  did; } ;
struct net_device {scalar_t__ addr_len; int /*<<< orphan*/ * dev_addr; scalar_t__ ml_priv; } ;
typedef  int /*<<< orphan*/  dot11req ;

/* Variables and functions */
 int /*<<< orphan*/  DIDMIB_DOT11MAC_OPERATIONTABLE_MACADDRESS ; 
 int /*<<< orphan*/  DIDMSG_DOT11REQ_MIBSET ; 
 int /*<<< orphan*/  DIDMSG_DOT11REQ_MIBSET_MIBATTRIBUTE ; 
 int /*<<< orphan*/  DIDMSG_DOT11REQ_MIBSET_RESULTCODE ; 
 int EADDRNOTAVAIL ; 
 int EBUSY ; 
 scalar_t__ ETH_ALEN ; 
 void* P80211ENUM_msgitem_status_data_ok ; 
 int /*<<< orphan*/  P80211ENUM_msgitem_status_no_value ; 
 scalar_t__ P80211ENUM_resultcode_success ; 
 scalar_t__ WLAN_DEVNAMELEN_MAX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct p80211msg_dot11req_mibset*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int p80211req_dorequest (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int p80211knetdev_set_mac_address(struct net_device *dev, void *addr)
{
	struct sockaddr *new_addr = addr;
	struct p80211msg_dot11req_mibset dot11req;
	struct p80211item_unk392 *mibattr;
	struct p80211item_pstr6 *macaddr;
	struct p80211item_uint32 *resultcode;
	int result;

	/* If we're running, we don't allow MAC address changes */
	if (netif_running(dev))
		return -EBUSY;

	/* Set up some convenience pointers. */
	mibattr = &dot11req.mibattribute;
	macaddr = (struct p80211item_pstr6 *)&mibattr->data;
	resultcode = &dot11req.resultcode;

	/* Set up a dot11req_mibset */
	memset(&dot11req, 0, sizeof(dot11req));
	dot11req.msgcode = DIDMSG_DOT11REQ_MIBSET;
	dot11req.msglen = sizeof(dot11req);
	memcpy(dot11req.devname,
	       ((struct wlandevice *)dev->ml_priv)->name,
	       WLAN_DEVNAMELEN_MAX - 1);

	/* Set up the mibattribute argument */
	mibattr->did = DIDMSG_DOT11REQ_MIBSET_MIBATTRIBUTE;
	mibattr->status = P80211ENUM_msgitem_status_data_ok;
	mibattr->len = sizeof(mibattr->data);

	macaddr->did = DIDMIB_DOT11MAC_OPERATIONTABLE_MACADDRESS;
	macaddr->status = P80211ENUM_msgitem_status_data_ok;
	macaddr->len = sizeof(macaddr->data);
	macaddr->data.len = ETH_ALEN;
	memcpy(&macaddr->data.data, new_addr->sa_data, ETH_ALEN);

	/* Set up the resultcode argument */
	resultcode->did = DIDMSG_DOT11REQ_MIBSET_RESULTCODE;
	resultcode->status = P80211ENUM_msgitem_status_no_value;
	resultcode->len = sizeof(resultcode->data);
	resultcode->data = 0;

	/* now fire the request */
	result = p80211req_dorequest(dev->ml_priv, (u8 *)&dot11req);

	/* If the request wasn't successful, report an error and don't
	 * change the netdev address
	 */
	if (result != 0 || resultcode->data != P80211ENUM_resultcode_success) {
		netdev_err(dev, "Low-level driver failed dot11req_mibset(dot11MACAddress).\n");
		result = -EADDRNOTAVAIL;
	} else {
		/* everything's ok, change the addr in netdev */
		memcpy(dev->dev_addr, new_addr->sa_data, dev->addr_len);
	}

	return result;
}