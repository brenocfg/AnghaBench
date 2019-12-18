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
typedef  size_t u8 ;
struct mlx5_ib_dev {TYPE_2__* port; } ;
struct TYPE_6__ {int /*<<< orphan*/ * notifier_call; } ;
struct TYPE_4__ {TYPE_3__ nb; } ;
struct TYPE_5__ {TYPE_1__ roce; } ;

/* Variables and functions */
 int /*<<< orphan*/  unregister_netdevice_notifier (TYPE_3__*) ; 

__attribute__((used)) static void mlx5_remove_netdev_notifier(struct mlx5_ib_dev *dev, u8 port_num)
{
	if (dev->port[port_num].roce.nb.notifier_call) {
		unregister_netdevice_notifier(&dev->port[port_num].roce.nb);
		dev->port[port_num].roce.nb.notifier_call = NULL;
	}
}