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
struct TYPE_2__ {int ctrlmode; } ;
struct softing_priv {TYPE_1__ can; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int CAN_CTRLMODE_BERR_REPORTING ; 
 struct softing_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline int softing_error_reporting(struct net_device *netdev)
{
	struct softing_priv *priv = netdev_priv(netdev);

	return (priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING)
		? 1 : 0;
}