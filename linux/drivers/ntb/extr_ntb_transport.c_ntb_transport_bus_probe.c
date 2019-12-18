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
struct ntb_transport_client {int (* probe ) (struct device*) ;} ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 struct ntb_transport_client* drv_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int stub1 (struct device*) ; 

__attribute__((used)) static int ntb_transport_bus_probe(struct device *dev)
{
	const struct ntb_transport_client *client;
	int rc;

	get_device(dev);

	client = drv_client(dev->driver);
	rc = client->probe(dev);
	if (rc)
		put_device(dev);

	return rc;
}