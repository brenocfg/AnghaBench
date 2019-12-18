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
struct qtnf_bus {TYPE_1__* bus_ops; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {void (* data_tx_timeout ) (struct qtnf_bus*,struct net_device*) ;} ;

/* Variables and functions */
 void stub1 (struct qtnf_bus*,struct net_device*) ; 

__attribute__((used)) static inline void
qtnf_bus_data_tx_timeout(struct qtnf_bus *bus, struct net_device *ndev)
{
	return bus->bus_ops->data_tx_timeout(bus, ndev);
}