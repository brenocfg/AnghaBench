#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_5__ {scalar_t__ iw_mode; int /*<<< orphan*/  monitor_type; TYPE_1__* ndev; } ;
typedef  TYPE_2__ islpci_private ;
typedef  scalar_t__ __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IEEE80211 ; 
 int /*<<< orphan*/  ARPHRD_IEEE80211_PRISM ; 
 scalar_t__ IW_MODE_MONITOR ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
prism54_set_prismhdr(struct net_device *ndev, struct iw_request_info *info,
		     __u32 * uwrq, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	priv->monitor_type =
	    (*uwrq ? ARPHRD_IEEE80211_PRISM : ARPHRD_IEEE80211);
	if (priv->iw_mode == IW_MODE_MONITOR)
		priv->ndev->type = priv->monitor_type;

	return 0;
}