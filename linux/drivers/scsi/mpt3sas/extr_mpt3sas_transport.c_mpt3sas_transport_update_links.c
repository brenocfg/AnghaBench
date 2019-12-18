#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct sas_identify {int dummy; } ;
struct TYPE_5__ {scalar_t__ sas_address; } ;
struct _sas_phy {TYPE_2__ remote_identify; TYPE_1__* phy; int /*<<< orphan*/  attached_handle; } ;
struct _sas_node {struct _sas_phy* phy; } ;
struct MPT3SAS_ADAPTER {int logging_level; int /*<<< orphan*/  sas_node_lock; scalar_t__ pci_error_recovery; scalar_t__ shost_recovery; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  negotiated_linkrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 size_t MPI2_SAS_NEG_LINK_RATE_1_5 ; 
 int MPT_DEBUG_TRANSPORT ; 
 int /*<<< orphan*/  _transport_add_phy_to_an_existing_port (struct MPT3SAS_ADAPTER*,struct _sas_node*,struct _sas_phy*,scalar_t__) ; 
 int /*<<< orphan*/  _transport_convert_phy_link_rate (size_t) ; 
 struct _sas_node* _transport_sas_node_find_by_sas_address (struct MPT3SAS_ADAPTER*,scalar_t__) ; 
 int /*<<< orphan*/  _transport_set_identify (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,unsigned long long,size_t,size_t,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
mpt3sas_transport_update_links(struct MPT3SAS_ADAPTER *ioc,
	u64 sas_address, u16 handle, u8 phy_number, u8 link_rate)
{
	unsigned long flags;
	struct _sas_node *sas_node;
	struct _sas_phy *mpt3sas_phy;

	if (ioc->shost_recovery || ioc->pci_error_recovery)
		return;

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	sas_node = _transport_sas_node_find_by_sas_address(ioc, sas_address);
	if (!sas_node) {
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
		return;
	}

	mpt3sas_phy = &sas_node->phy[phy_number];
	mpt3sas_phy->attached_handle = handle;
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
	if (handle && (link_rate >= MPI2_SAS_NEG_LINK_RATE_1_5)) {
		_transport_set_identify(ioc, handle,
		    &mpt3sas_phy->remote_identify);
		_transport_add_phy_to_an_existing_port(ioc, sas_node,
		    mpt3sas_phy, mpt3sas_phy->remote_identify.sas_address);
	} else
		memset(&mpt3sas_phy->remote_identify, 0 , sizeof(struct
		    sas_identify));

	if (mpt3sas_phy->phy)
		mpt3sas_phy->phy->negotiated_linkrate =
		    _transport_convert_phy_link_rate(link_rate);

	if ((ioc->logging_level & MPT_DEBUG_TRANSPORT))
		dev_printk(KERN_INFO, &mpt3sas_phy->phy->dev,
		    "refresh: parent sas_addr(0x%016llx),\n"
		    "\tlink_rate(0x%02x), phy(%d)\n"
		    "\tattached_handle(0x%04x), sas_addr(0x%016llx)\n",
		    (unsigned long long)sas_address,
		    link_rate, phy_number, handle, (unsigned long long)
		    mpt3sas_phy->remote_identify.sas_address);
}