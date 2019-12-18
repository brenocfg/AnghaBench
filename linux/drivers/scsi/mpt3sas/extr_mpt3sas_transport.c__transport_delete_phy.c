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
typedef  scalar_t__ u64 ;
struct TYPE_3__ {scalar_t__ sas_address; } ;
struct _sas_port {int /*<<< orphan*/  port; int /*<<< orphan*/  num_phys; TYPE_1__ remote_identify; } ;
struct _sas_phy {scalar_t__ phy_belongs_to_port; TYPE_2__* phy; int /*<<< orphan*/  port_siblings; int /*<<< orphan*/  phy_id; } ;
struct MPT3SAS_ADAPTER {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_port_delete_phy (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void
_transport_delete_phy(struct MPT3SAS_ADAPTER *ioc,
	struct _sas_port *mpt3sas_port, struct _sas_phy *mpt3sas_phy)
{
	u64 sas_address = mpt3sas_port->remote_identify.sas_address;

	dev_printk(KERN_INFO, &mpt3sas_phy->phy->dev,
	    "remove: sas_addr(0x%016llx), phy(%d)\n",
	    (unsigned long long) sas_address, mpt3sas_phy->phy_id);

	list_del(&mpt3sas_phy->port_siblings);
	mpt3sas_port->num_phys--;
	sas_port_delete_phy(mpt3sas_port->port, mpt3sas_phy->phy);
	mpt3sas_phy->phy_belongs_to_port = 0;
}