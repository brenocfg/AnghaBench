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
typedef  int u32 ;
struct r8192_priv {int crcmon; TYPE_1__* ieee80211; } ;
struct net_device {int flags; } ;
struct TYPE_2__ {scalar_t__ iw_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMESG (char*) ; 
 int IFF_PROMISC ; 
 scalar_t__ IW_MODE_MONITOR ; 
 int MAC_FILTER_MASK ; 
 int MAX_RX_DMA_MASK ; 
 int /*<<< orphan*/  RCR ; 
 int RCR_AAP ; 
 int RCR_AB ; 
 int RCR_ACRC32 ; 
 int RCR_ADF ; 
 int RCR_AICV ; 
 int RCR_AM ; 
 int RCR_AMF ; 
 int RCR_APM ; 
 int RCR_APWRMGT ; 
 int RCR_CBSSID ; 
 int RCR_MXDMA_OFFSET ; 
 int RCR_ONLYERLPKT ; 
 int RX_FIFO_THRESHOLD_MASK ; 
 int RX_FIFO_THRESHOLD_NONE ; 
 int RX_FIFO_THRESHOLD_SHIFT ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  read_nic_dword (struct net_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int) ; 

void rtl8192_set_rxconf(struct net_device *dev)
{
	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);
	u32 rxconf;

	read_nic_dword(dev, RCR, &rxconf);
	rxconf = rxconf & ~MAC_FILTER_MASK;
	rxconf = rxconf | RCR_AMF;
	rxconf = rxconf | RCR_ADF;
	rxconf = rxconf | RCR_AB;
	rxconf = rxconf | RCR_AM;

	if (dev->flags & IFF_PROMISC)
		DMESG("NIC in promisc mode");

	if (priv->ieee80211->iw_mode == IW_MODE_MONITOR ||
	    dev->flags & IFF_PROMISC) {
		rxconf = rxconf | RCR_AAP;
	} else {
		rxconf = rxconf | RCR_APM;
		rxconf = rxconf | RCR_CBSSID;
	}


	if (priv->ieee80211->iw_mode == IW_MODE_MONITOR) {
		rxconf = rxconf | RCR_AICV;
		rxconf = rxconf | RCR_APWRMGT;
	}

	if (priv->crcmon == 1 && priv->ieee80211->iw_mode == IW_MODE_MONITOR)
		rxconf = rxconf | RCR_ACRC32;


	rxconf = rxconf & ~RX_FIFO_THRESHOLD_MASK;
	rxconf = rxconf | (RX_FIFO_THRESHOLD_NONE << RX_FIFO_THRESHOLD_SHIFT);
	rxconf = rxconf & ~MAX_RX_DMA_MASK;
	rxconf = rxconf | ((u32)7 << RCR_MXDMA_OFFSET);

	rxconf = rxconf | RCR_ONLYERLPKT;

	write_nic_dword(dev, RCR, rxconf);
}