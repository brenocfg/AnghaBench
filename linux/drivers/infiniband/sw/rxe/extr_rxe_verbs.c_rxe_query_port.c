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
typedef  int /*<<< orphan*/  u8 ;
struct ib_port_attr {scalar_t__ state; int /*<<< orphan*/  phys_state; int /*<<< orphan*/  active_width; int /*<<< orphan*/  active_speed; } ;
struct rxe_port {struct ib_port_attr attr; } ;
struct rxe_dev {int /*<<< orphan*/  usdev_lock; int /*<<< orphan*/  ndev; struct rxe_port port; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IB_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_PORT_PHYS_STATE_DISABLED ; 
 int /*<<< orphan*/  IB_PORT_PHYS_STATE_LINK_UP ; 
 int /*<<< orphan*/  IB_PORT_PHYS_STATE_POLLING ; 
 int IFF_UP ; 
 int dev_get_flags (int /*<<< orphan*/ ) ; 
 int ib_get_eth_speed (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rxe_dev* to_rdev (struct ib_device*) ; 

__attribute__((used)) static int rxe_query_port(struct ib_device *dev,
			  u8 port_num, struct ib_port_attr *attr)
{
	struct rxe_dev *rxe = to_rdev(dev);
	struct rxe_port *port;
	int rc;

	port = &rxe->port;

	/* *attr being zeroed by the caller, avoid zeroing it here */
	*attr = port->attr;

	mutex_lock(&rxe->usdev_lock);
	rc = ib_get_eth_speed(dev, port_num, &attr->active_speed,
			      &attr->active_width);

	if (attr->state == IB_PORT_ACTIVE)
		attr->phys_state = IB_PORT_PHYS_STATE_LINK_UP;
	else if (dev_get_flags(rxe->ndev) & IFF_UP)
		attr->phys_state = IB_PORT_PHYS_STATE_POLLING;
	else
		attr->phys_state = IB_PORT_PHYS_STATE_DISABLED;

	mutex_unlock(&rxe->usdev_lock);

	return rc;
}