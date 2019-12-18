#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long txbytesunicast; unsigned long rxbytesunicast; } ;
struct r8192_priv {TYPE_2__ stats; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {scalar_t__ IOTPeer; int /*<<< orphan*/  IOTAction; } ;
struct TYPE_4__ {int bCTSToSelfEnable; TYPE_3__* pHTInfo; } ;
typedef  TYPE_3__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */
 int /*<<< orphan*/  HT_IOT_ACT_FORCED_CTS2SELF ; 
 scalar_t__ HT_IOT_PEER_BROADCOM ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static void dm_ctstoself(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	PRT_HIGH_THROUGHPUT	pHTInfo = priv->ieee80211->pHTInfo;
	static unsigned long				lastTxOkCnt;
	static unsigned long				lastRxOkCnt;
	unsigned long						curTxOkCnt = 0;
	unsigned long						curRxOkCnt = 0;

	if (priv->ieee80211->bCTSToSelfEnable != true) {
		pHTInfo->IOTAction &= ~HT_IOT_ACT_FORCED_CTS2SELF;
		return;
	}
	/* 1. Uplink
	 * 2. Linksys350/Linksys300N
	 * 3. <50 disable, >55 enable
	 */

	if (pHTInfo->IOTPeer == HT_IOT_PEER_BROADCOM) {
		curTxOkCnt = priv->stats.txbytesunicast - lastTxOkCnt;
		curRxOkCnt = priv->stats.rxbytesunicast - lastRxOkCnt;
		if (curRxOkCnt > 4*curTxOkCnt) { /* downlink, disable CTS to self */
			pHTInfo->IOTAction &= ~HT_IOT_ACT_FORCED_CTS2SELF;
			/*DbgPrint("dm_CTSToSelf() ==> CTS to self disabled -- downlink\n");*/
		} else { /* uplink */
			pHTInfo->IOTAction |= HT_IOT_ACT_FORCED_CTS2SELF;
		}

		lastTxOkCnt = priv->stats.txbytesunicast;
		lastRxOkCnt = priv->stats.rxbytesunicast;
	}
}