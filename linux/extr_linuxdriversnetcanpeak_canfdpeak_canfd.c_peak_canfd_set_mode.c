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
struct peak_canfd_priv {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum can_mode { ____Placeholder_can_mode } can_mode ;

/* Variables and functions */
#define  CAN_MODE_START 128 
 int EOPNOTSUPP ; 
 struct peak_canfd_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  peak_canfd_start (struct peak_canfd_priv*) ; 

__attribute__((used)) static int peak_canfd_set_mode(struct net_device *ndev, enum can_mode mode)
{
	struct peak_canfd_priv *priv = netdev_priv(ndev);

	switch (mode) {
	case CAN_MODE_START:
		peak_canfd_start(priv);
		netif_wake_queue(ndev);
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}