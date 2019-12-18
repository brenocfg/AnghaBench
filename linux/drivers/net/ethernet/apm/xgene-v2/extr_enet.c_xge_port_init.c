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
struct xge_pdata {int /*<<< orphan*/  phy_speed; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPEED_1000 ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  xge_mac_init (struct xge_pdata*) ; 
 int /*<<< orphan*/  xge_traffic_resume (struct net_device*) ; 

void xge_port_init(struct net_device *ndev)
{
	struct xge_pdata *pdata = netdev_priv(ndev);

	pdata->phy_speed = SPEED_1000;
	xge_mac_init(pdata);
	xge_traffic_resume(ndev);
}