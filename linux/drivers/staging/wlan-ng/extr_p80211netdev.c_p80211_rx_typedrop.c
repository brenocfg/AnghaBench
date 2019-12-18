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
struct TYPE_3__ {int /*<<< orphan*/  data_unknown; int /*<<< orphan*/  cfack_cfpoll; int /*<<< orphan*/  cfpoll; int /*<<< orphan*/  cfack; int /*<<< orphan*/  null; int /*<<< orphan*/  data__cfack_cfpoll; int /*<<< orphan*/  data_cfpoll; int /*<<< orphan*/  data_cfack; int /*<<< orphan*/  dataonly; int /*<<< orphan*/  data; int /*<<< orphan*/  ctl_unknown; int /*<<< orphan*/  cfendcfack; int /*<<< orphan*/  cfend; int /*<<< orphan*/  ack; int /*<<< orphan*/  cts; int /*<<< orphan*/  rts; int /*<<< orphan*/  pspoll; int /*<<< orphan*/  ctl; int /*<<< orphan*/  mgmt_unknown; int /*<<< orphan*/  deauthen; int /*<<< orphan*/  authen; int /*<<< orphan*/  disassoc; int /*<<< orphan*/  atim; int /*<<< orphan*/  beacon; int /*<<< orphan*/  proberesp; int /*<<< orphan*/  probereq; int /*<<< orphan*/  reassocresp; int /*<<< orphan*/  reassocreq; int /*<<< orphan*/  assocresp; int /*<<< orphan*/  assocreq; int /*<<< orphan*/  mgmt; } ;
struct wlandevice {TYPE_1__ rx; TYPE_2__* netdev; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
#define  WLAN_FSTYPE_ACK 155 
#define  WLAN_FSTYPE_ASSOCREQ 154 
#define  WLAN_FSTYPE_ASSOCRESP 153 
#define  WLAN_FSTYPE_ATIM 152 
#define  WLAN_FSTYPE_AUTHEN 151 
#define  WLAN_FSTYPE_BEACON 150 
#define  WLAN_FSTYPE_CFACK 149 
#define  WLAN_FSTYPE_CFACK_CFPOLL 148 
#define  WLAN_FSTYPE_CFEND 147 
#define  WLAN_FSTYPE_CFENDCFACK 146 
#define  WLAN_FSTYPE_CFPOLL 145 
#define  WLAN_FSTYPE_CTS 144 
#define  WLAN_FSTYPE_DATAONLY 143 
#define  WLAN_FSTYPE_DATA_CFACK 142 
#define  WLAN_FSTYPE_DATA_CFACK_CFPOLL 141 
#define  WLAN_FSTYPE_DATA_CFPOLL 140 
#define  WLAN_FSTYPE_DEAUTHEN 139 
#define  WLAN_FSTYPE_DISASSOC 138 
#define  WLAN_FSTYPE_NULL 137 
#define  WLAN_FSTYPE_PROBEREQ 136 
#define  WLAN_FSTYPE_PROBERESP 135 
#define  WLAN_FSTYPE_PSPOLL 134 
#define  WLAN_FSTYPE_REASSOCREQ 133 
#define  WLAN_FSTYPE_REASSOCRESP 132 
#define  WLAN_FSTYPE_RTS 131 
#define  WLAN_FTYPE_CTL 130 
#define  WLAN_FTYPE_DATA 129 
#define  WLAN_FTYPE_MGMT 128 
 int WLAN_GET_FC_FSTYPE (int) ; 
 int WLAN_GET_FC_FTYPE (int) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_2__*,char*) ; 

__attribute__((used)) static int p80211_rx_typedrop(struct wlandevice *wlandev, u16 fc)
{
	u16 ftype;
	u16 fstype;
	int drop = 0;
	/* Classify frame, increment counter */
	ftype = WLAN_GET_FC_FTYPE(fc);
	fstype = WLAN_GET_FC_FSTYPE(fc);
	switch (ftype) {
	case WLAN_FTYPE_MGMT:
		if ((wlandev->netdev->flags & IFF_PROMISC) ||
		    (wlandev->netdev->flags & IFF_ALLMULTI)) {
			drop = 1;
			break;
		}
		netdev_dbg(wlandev->netdev, "rx'd mgmt:\n");
		wlandev->rx.mgmt++;
		switch (fstype) {
		case WLAN_FSTYPE_ASSOCREQ:
			/* printk("assocreq"); */
			wlandev->rx.assocreq++;
			break;
		case WLAN_FSTYPE_ASSOCRESP:
			/* printk("assocresp"); */
			wlandev->rx.assocresp++;
			break;
		case WLAN_FSTYPE_REASSOCREQ:
			/* printk("reassocreq"); */
			wlandev->rx.reassocreq++;
			break;
		case WLAN_FSTYPE_REASSOCRESP:
			/* printk("reassocresp"); */
			wlandev->rx.reassocresp++;
			break;
		case WLAN_FSTYPE_PROBEREQ:
			/* printk("probereq"); */
			wlandev->rx.probereq++;
			break;
		case WLAN_FSTYPE_PROBERESP:
			/* printk("proberesp"); */
			wlandev->rx.proberesp++;
			break;
		case WLAN_FSTYPE_BEACON:
			/* printk("beacon"); */
			wlandev->rx.beacon++;
			break;
		case WLAN_FSTYPE_ATIM:
			/* printk("atim"); */
			wlandev->rx.atim++;
			break;
		case WLAN_FSTYPE_DISASSOC:
			/* printk("disassoc"); */
			wlandev->rx.disassoc++;
			break;
		case WLAN_FSTYPE_AUTHEN:
			/* printk("authen"); */
			wlandev->rx.authen++;
			break;
		case WLAN_FSTYPE_DEAUTHEN:
			/* printk("deauthen"); */
			wlandev->rx.deauthen++;
			break;
		default:
			/* printk("unknown"); */
			wlandev->rx.mgmt_unknown++;
			break;
		}
		/* printk("\n"); */
		drop = 2;
		break;

	case WLAN_FTYPE_CTL:
		if ((wlandev->netdev->flags & IFF_PROMISC) ||
		    (wlandev->netdev->flags & IFF_ALLMULTI)) {
			drop = 1;
			break;
		}
		netdev_dbg(wlandev->netdev, "rx'd ctl:\n");
		wlandev->rx.ctl++;
		switch (fstype) {
		case WLAN_FSTYPE_PSPOLL:
			/* printk("pspoll"); */
			wlandev->rx.pspoll++;
			break;
		case WLAN_FSTYPE_RTS:
			/* printk("rts"); */
			wlandev->rx.rts++;
			break;
		case WLAN_FSTYPE_CTS:
			/* printk("cts"); */
			wlandev->rx.cts++;
			break;
		case WLAN_FSTYPE_ACK:
			/* printk("ack"); */
			wlandev->rx.ack++;
			break;
		case WLAN_FSTYPE_CFEND:
			/* printk("cfend"); */
			wlandev->rx.cfend++;
			break;
		case WLAN_FSTYPE_CFENDCFACK:
			/* printk("cfendcfack"); */
			wlandev->rx.cfendcfack++;
			break;
		default:
			/* printk("unknown"); */
			wlandev->rx.ctl_unknown++;
			break;
		}
		/* printk("\n"); */
		drop = 2;
		break;

	case WLAN_FTYPE_DATA:
		wlandev->rx.data++;
		switch (fstype) {
		case WLAN_FSTYPE_DATAONLY:
			wlandev->rx.dataonly++;
			break;
		case WLAN_FSTYPE_DATA_CFACK:
			wlandev->rx.data_cfack++;
			break;
		case WLAN_FSTYPE_DATA_CFPOLL:
			wlandev->rx.data_cfpoll++;
			break;
		case WLAN_FSTYPE_DATA_CFACK_CFPOLL:
			wlandev->rx.data__cfack_cfpoll++;
			break;
		case WLAN_FSTYPE_NULL:
			netdev_dbg(wlandev->netdev, "rx'd data:null\n");
			wlandev->rx.null++;
			break;
		case WLAN_FSTYPE_CFACK:
			netdev_dbg(wlandev->netdev, "rx'd data:cfack\n");
			wlandev->rx.cfack++;
			break;
		case WLAN_FSTYPE_CFPOLL:
			netdev_dbg(wlandev->netdev, "rx'd data:cfpoll\n");
			wlandev->rx.cfpoll++;
			break;
		case WLAN_FSTYPE_CFACK_CFPOLL:
			netdev_dbg(wlandev->netdev, "rx'd data:cfack_cfpoll\n");
			wlandev->rx.cfack_cfpoll++;
			break;
		default:
			/* printk("unknown"); */
			wlandev->rx.data_unknown++;
			break;
		}

		break;
	}
	return drop;
}