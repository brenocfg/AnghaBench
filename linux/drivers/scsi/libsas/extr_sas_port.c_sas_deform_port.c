#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sas_internal {TYPE_3__* dft; } ;
struct TYPE_5__ {TYPE_1__* shost; } ;
struct sas_ha_struct {int /*<<< orphan*/  disco_q; int /*<<< orphan*/  phy_port_lock; TYPE_2__ core; } ;
struct expander_device {int ex_change_count; } ;
struct domain_device {struct expander_device ex_dev; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  pathways; } ;
struct asd_sas_port {int num_phys; unsigned int phy_mask; int /*<<< orphan*/ * port; int /*<<< orphan*/  phy_list_lock; scalar_t__ oob_mode; scalar_t__ tproto; scalar_t__ iproto; scalar_t__ class; int /*<<< orphan*/  attached_sas_addr; int /*<<< orphan*/  sas_addr; int /*<<< orphan*/  phy_list; struct domain_device* port_dev; } ;
struct asd_sas_phy {unsigned int id; struct asd_sas_port* port; int /*<<< orphan*/  port_phy_el; int /*<<< orphan*/  phy; struct sas_ha_struct* ha; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* lldd_port_deformed ) (struct asd_sas_phy*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  transportt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCE_REVALIDATE_DOMAIN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 scalar_t__ dev_is_expander (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_destruct_devices (struct asd_sas_port*) ; 
 int /*<<< orphan*/  sas_device_set_phy (struct domain_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_discover_event (struct asd_sas_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_phy_set_target (struct asd_sas_phy*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_port_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_port_delete_phy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_unregister_domain_devices (struct asd_sas_port*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct asd_sas_phy*) ; 
 struct sas_internal* to_sas_internal (int /*<<< orphan*/ ) ; 

void sas_deform_port(struct asd_sas_phy *phy, int gone)
{
	struct sas_ha_struct *sas_ha = phy->ha;
	struct asd_sas_port *port = phy->port;
	struct sas_internal *si =
		to_sas_internal(sas_ha->core.shost->transportt);
	struct domain_device *dev;
	unsigned long flags;

	if (!port)
		return;		  /* done by a phy event */

	dev = port->port_dev;
	if (dev)
		dev->pathways--;

	if (port->num_phys == 1) {
		sas_unregister_domain_devices(port, gone);
		sas_destruct_devices(port);
		sas_port_delete(port->port);
		port->port = NULL;
	} else {
		sas_port_delete_phy(port->port, phy->phy);
		sas_device_set_phy(dev, port->port);
	}

	if (si->dft->lldd_port_deformed)
		si->dft->lldd_port_deformed(phy);

	spin_lock_irqsave(&sas_ha->phy_port_lock, flags);
	spin_lock(&port->phy_list_lock);

	list_del_init(&phy->port_phy_el);
	sas_phy_set_target(phy, NULL);
	phy->port = NULL;
	port->num_phys--;
	port->phy_mask &= ~(1U << phy->id);

	if (port->num_phys == 0) {
		INIT_LIST_HEAD(&port->phy_list);
		memset(port->sas_addr, 0, SAS_ADDR_SIZE);
		memset(port->attached_sas_addr, 0, SAS_ADDR_SIZE);
		port->class = 0;
		port->iproto = 0;
		port->tproto = 0;
		port->oob_mode = 0;
		port->phy_mask = 0;
	}
	spin_unlock(&port->phy_list_lock);
	spin_unlock_irqrestore(&sas_ha->phy_port_lock, flags);

	/* Only insert revalidate event if the port still has members */
	if (port->port && dev && dev_is_expander(dev->dev_type)) {
		struct expander_device *ex_dev = &dev->ex_dev;

		ex_dev->ex_change_count = -1;
		sas_discover_event(port, DISCE_REVALIDATE_DOMAIN);
	}
	flush_workqueue(sas_ha->disco_q);

	return;
}