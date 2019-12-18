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
struct TYPE_2__ {int /*<<< orphan*/  clock; } ;
struct ravb_private {TYPE_1__ ptp; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIC ; 
 int /*<<< orphan*/  GIS ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ravb_write (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ravb_ptp_stop(struct net_device *ndev)
{
	struct ravb_private *priv = netdev_priv(ndev);

	ravb_write(ndev, 0, GIC);
	ravb_write(ndev, 0, GIS);

	ptp_clock_unregister(priv->ptp.clock);
}