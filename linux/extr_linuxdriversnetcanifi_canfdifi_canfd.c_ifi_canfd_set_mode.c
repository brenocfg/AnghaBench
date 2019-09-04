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
struct net_device {int dummy; } ;
typedef  enum can_mode { ____Placeholder_can_mode } can_mode ;

/* Variables and functions */
#define  CAN_MODE_START 128 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ifi_canfd_start (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static int ifi_canfd_set_mode(struct net_device *ndev, enum can_mode mode)
{
	switch (mode) {
	case CAN_MODE_START:
		ifi_canfd_start(ndev);
		netif_wake_queue(ndev);
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}