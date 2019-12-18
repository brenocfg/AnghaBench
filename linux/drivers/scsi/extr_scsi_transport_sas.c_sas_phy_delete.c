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
struct device {int dummy; } ;
struct sas_phy {int /*<<< orphan*/  port_siblings; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  device_del (struct device*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  transport_destroy_device (struct device*) ; 
 int /*<<< orphan*/  transport_remove_device (struct device*) ; 

void
sas_phy_delete(struct sas_phy *phy)
{
	struct device *dev = &phy->dev;

	/* this happens if the phy is still part of a port when deleted */
	BUG_ON(!list_empty(&phy->port_siblings));

	transport_remove_device(dev);
	device_del(dev);
	transport_destroy_device(dev);
	put_device(dev);
}