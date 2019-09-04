#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {size_t if_port; int mtu; struct adapter* ml_priv; } ;
struct cmac {TYPE_2__* ops; } ;
struct adapter {TYPE_1__* port; } ;
struct TYPE_4__ {int (* set_mtu ) (struct cmac*,int) ;} ;
struct TYPE_3__ {struct cmac* mac; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct cmac*,int) ; 

__attribute__((used)) static int t1_change_mtu(struct net_device *dev, int new_mtu)
{
	int ret;
	struct adapter *adapter = dev->ml_priv;
	struct cmac *mac = adapter->port[dev->if_port].mac;

	if (!mac->ops->set_mtu)
		return -EOPNOTSUPP;
	if ((ret = mac->ops->set_mtu(mac, new_mtu)))
		return ret;
	dev->mtu = new_mtu;
	return 0;
}