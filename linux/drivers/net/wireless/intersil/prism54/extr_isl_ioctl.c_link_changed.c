#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union iwreq_data {int dummy; } iwreq_data ;
typedef  scalar_t__ u32 ;
struct sockaddr {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ iw_mode; } ;
typedef  TYPE_1__ islpci_private ;

/* Variables and functions */
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  prism54_get_wap (struct net_device*,int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_simple_event (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  wireless_send_event (struct net_device*,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
link_changed(struct net_device *ndev, u32 bitrate)
{
	islpci_private *priv = netdev_priv(ndev);

	if (bitrate) {
		netif_carrier_on(ndev);
		if (priv->iw_mode == IW_MODE_INFRA) {
			union iwreq_data uwrq;
			prism54_get_wap(ndev, NULL, (struct sockaddr *) &uwrq,
					NULL);
			wireless_send_event(ndev, SIOCGIWAP, &uwrq, NULL);
		} else
			send_simple_event(netdev_priv(ndev),
					  "Link established");
	} else {
		netif_carrier_off(ndev);
		send_simple_event(netdev_priv(ndev), "Link lost");
	}
}