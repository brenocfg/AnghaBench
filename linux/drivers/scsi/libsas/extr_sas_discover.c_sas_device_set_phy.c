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
struct sas_port {int dummy; } ;
struct sas_phy {int dummy; } ;
struct sas_ha_struct {int /*<<< orphan*/  phy_port_lock; } ;
struct domain_device {struct sas_phy* phy; TYPE_1__* port; } ;
struct TYPE_2__ {struct sas_ha_struct* ha; } ;

/* Variables and functions */
 struct sas_phy* sas_port_get_phy (struct sas_port*) ; 
 int /*<<< orphan*/  sas_port_put_phy (struct sas_phy*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void sas_device_set_phy(struct domain_device *dev, struct sas_port *port)
{
	struct sas_ha_struct *ha;
	struct sas_phy *new_phy;

	if (!dev)
		return;

	ha = dev->port->ha;
	new_phy = sas_port_get_phy(port);

	/* pin and record last seen phy */
	spin_lock_irq(&ha->phy_port_lock);
	if (new_phy) {
		sas_port_put_phy(dev->phy);
		dev->phy = new_phy;
	}
	spin_unlock_irq(&ha->phy_port_lock);
}