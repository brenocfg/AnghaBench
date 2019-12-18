#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sas_rphy {int /*<<< orphan*/  dev; } ;
struct sas_expander_device {scalar_t__ level; } ;
struct ex_phy {scalar_t__ routing_attr; int attached_dev_type; int /*<<< orphan*/ * port; int /*<<< orphan*/  attached_sas_addr; int /*<<< orphan*/  attached_tproto; int /*<<< orphan*/  attached_iproto; int /*<<< orphan*/  attached_phy_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  children; struct ex_phy* ex_phy; } ;
struct domain_device {int dev_type; TYPE_2__ ex_dev; int /*<<< orphan*/  siblings; struct asd_sas_port* port; int /*<<< orphan*/  dev_list_node; int /*<<< orphan*/  sas_addr; int /*<<< orphan*/  hashed_sas_addr; int /*<<< orphan*/  tproto; int /*<<< orphan*/  iproto; struct domain_device* parent; int /*<<< orphan*/  kref; struct sas_rphy* rphy; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_level; } ;
struct asd_sas_port {int /*<<< orphan*/  dev_list_lock; int /*<<< orphan*/  dev_list; TYPE_1__ disc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DIRECT_ROUTING ; 
 int /*<<< orphan*/  SAS_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
#define  SAS_EDGE_EXPANDER_DEVICE 129 
#define  SAS_FANOUT_EXPANDER_DEVICE 128 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sas_expander_device* rphy_to_expander_device (struct sas_rphy*) ; 
 struct domain_device* sas_alloc_device () ; 
 int sas_discover_expander (struct domain_device*) ; 
 int /*<<< orphan*/  sas_ex_get_linkrate (struct domain_device*,struct domain_device*,struct ex_phy*) ; 
 struct sas_rphy* sas_expander_alloc (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  sas_fill_in_rphy (struct domain_device*,struct sas_rphy*) ; 
 int /*<<< orphan*/  sas_hash_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_init_dev (struct domain_device*) ; 
 scalar_t__ sas_port_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sas_port_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sas_port_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_put_device (struct domain_device*) ; 
 int /*<<< orphan*/  sas_rphy_add (struct sas_rphy*) ; 
 int /*<<< orphan*/  sas_rphy_delete (struct sas_rphy*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct domain_device *sas_ex_discover_expander(
	struct domain_device *parent, int phy_id)
{
	struct sas_expander_device *parent_ex = rphy_to_expander_device(parent->rphy);
	struct ex_phy *phy = &parent->ex_dev.ex_phy[phy_id];
	struct domain_device *child = NULL;
	struct sas_rphy *rphy;
	struct sas_expander_device *edev;
	struct asd_sas_port *port;
	int res;

	if (phy->routing_attr == DIRECT_ROUTING) {
		pr_warn("ex %016llx:%02d:D <--> ex %016llx:0x%x is not allowed\n",
			SAS_ADDR(parent->sas_addr), phy_id,
			SAS_ADDR(phy->attached_sas_addr),
			phy->attached_phy_id);
		return NULL;
	}
	child = sas_alloc_device();
	if (!child)
		return NULL;

	phy->port = sas_port_alloc(&parent->rphy->dev, phy_id);
	/* FIXME: better error handling */
	BUG_ON(sas_port_add(phy->port) != 0);


	switch (phy->attached_dev_type) {
	case SAS_EDGE_EXPANDER_DEVICE:
		rphy = sas_expander_alloc(phy->port,
					  SAS_EDGE_EXPANDER_DEVICE);
		break;
	case SAS_FANOUT_EXPANDER_DEVICE:
		rphy = sas_expander_alloc(phy->port,
					  SAS_FANOUT_EXPANDER_DEVICE);
		break;
	default:
		rphy = NULL;	/* shut gcc up */
		BUG();
	}
	port = parent->port;
	child->rphy = rphy;
	get_device(&rphy->dev);
	edev = rphy_to_expander_device(rphy);
	child->dev_type = phy->attached_dev_type;
	kref_get(&parent->kref);
	child->parent = parent;
	child->port = port;
	child->iproto = phy->attached_iproto;
	child->tproto = phy->attached_tproto;
	memcpy(child->sas_addr, phy->attached_sas_addr, SAS_ADDR_SIZE);
	sas_hash_addr(child->hashed_sas_addr, child->sas_addr);
	sas_ex_get_linkrate(parent, child, phy);
	edev->level = parent_ex->level + 1;
	parent->port->disc.max_level = max(parent->port->disc.max_level,
					   edev->level);
	sas_init_dev(child);
	sas_fill_in_rphy(child, rphy);
	sas_rphy_add(rphy);

	spin_lock_irq(&parent->port->dev_list_lock);
	list_add_tail(&child->dev_list_node, &parent->port->dev_list);
	spin_unlock_irq(&parent->port->dev_list_lock);

	res = sas_discover_expander(child);
	if (res) {
		sas_rphy_delete(rphy);
		spin_lock_irq(&parent->port->dev_list_lock);
		list_del(&child->dev_list_node);
		spin_unlock_irq(&parent->port->dev_list_lock);
		sas_put_device(child);
		sas_port_delete(phy->port);
		phy->port = NULL;
		return NULL;
	}
	list_add_tail(&child->siblings, &parent->ex_dev.children);
	return child;
}