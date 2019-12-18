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
struct rtllib_rx_stats {int /*<<< orphan*/  mac_time; int /*<<< orphan*/  bFirstMPDU; scalar_t__ bIsAMPDU; } ;
struct r8192_priv {int /*<<< orphan*/  LastRxDescTSF; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

void rtl92e_update_rx_pkt_timestamp(struct net_device *dev,
				    struct rtllib_rx_stats *stats)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	if (stats->bIsAMPDU && !stats->bFirstMPDU)
		stats->mac_time = priv->LastRxDescTSF;
	else
		priv->LastRxDescTSF = stats->mac_time;
}