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
struct port_info {struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int dbqtimer_tick; } ;
struct adapter {int flags; TYPE_1__ sge; } ;

/* Variables and functions */
 int CXGB4_SGE_DBQ_TIMER ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int get_dbqtimer_tick(struct net_device *dev)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adap = pi->adapter;

	if (!(adap->flags & CXGB4_SGE_DBQ_TIMER))
		return 0;

	return adap->sge.dbqtimer_tick;
}