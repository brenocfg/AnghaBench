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
struct phy_device {int /*<<< orphan*/  link; } ;
struct ksz_port {int read; } ;
struct ksz_device {int live_ports; int on_ports; int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/  mib_read; struct ksz_port* ports; } ;
struct dsa_switch {struct ksz_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void ksz_adjust_link(struct dsa_switch *ds, int port,
		     struct phy_device *phydev)
{
	struct ksz_device *dev = ds->priv;
	struct ksz_port *p = &dev->ports[port];

	/* Read all MIB counters when the link is going down. */
	if (!phydev->link) {
		p->read = true;
		schedule_work(&dev->mib_read);
	}
	mutex_lock(&dev->dev_mutex);
	if (!phydev->link)
		dev->live_ports &= ~(1 << port);
	else
		/* Remember which port is connected and active. */
		dev->live_ports |= (1 << port) & dev->on_ports;
	mutex_unlock(&dev->dev_mutex);
}