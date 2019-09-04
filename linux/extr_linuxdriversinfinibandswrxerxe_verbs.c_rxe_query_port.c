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
typedef  int u8 ;
struct ib_port_attr {int /*<<< orphan*/  active_width; int /*<<< orphan*/  active_speed; } ;
struct rxe_port {struct ib_port_attr attr; } ;
struct rxe_dev {int /*<<< orphan*/  usdev_lock; struct rxe_port port; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ib_get_eth_speed (struct ib_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 struct rxe_dev* to_rdev (struct ib_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rxe_query_port(struct ib_device *dev,
			  u8 port_num, struct ib_port_attr *attr)
{
	struct rxe_dev *rxe = to_rdev(dev);
	struct rxe_port *port;
	int rc = -EINVAL;

	if (unlikely(port_num != 1)) {
		pr_warn("invalid port_number %d\n", port_num);
		goto out;
	}

	port = &rxe->port;

	/* *attr being zeroed by the caller, avoid zeroing it here */
	*attr = port->attr;

	mutex_lock(&rxe->usdev_lock);
	rc = ib_get_eth_speed(dev, port_num, &attr->active_speed,
			      &attr->active_width);
	mutex_unlock(&rxe->usdev_lock);

out:
	return rc;
}