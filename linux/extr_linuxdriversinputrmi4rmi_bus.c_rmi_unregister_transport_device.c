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
struct rmi_transport_dev {struct rmi_device* rmi_dev; } ;
struct rmi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

void rmi_unregister_transport_device(struct rmi_transport_dev *xport)
{
	struct rmi_device *rmi_dev = xport->rmi_dev;

	device_del(&rmi_dev->dev);
	put_device(&rmi_dev->dev);
}