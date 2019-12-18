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
struct adapter {int /*<<< orphan*/  hw_init_mutex; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int _netdev_open (struct net_device*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 

int netdev_open(struct net_device *pnetdev)
{
	int ret;
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(pnetdev);

	if (mutex_lock_interruptible(&padapter->hw_init_mutex))
		return -ERESTARTSYS;
	ret = _netdev_open(pnetdev);
	mutex_unlock(&padapter->hw_init_mutex);
	return ret;
}