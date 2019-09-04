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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pci_func; int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {int physical_port; TYPE_1__ ahw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRB_XG_STATE ; 
 int /*<<< orphan*/  CRB_XG_STATE_P3 ; 
 int NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ NX_IS_REVISION_P3 (int /*<<< orphan*/ ) ; 
 int XG_LINK_STATE_P3 (int /*<<< orphan*/ ,int) ; 
 int XG_LINK_UP ; 
 int XG_LINK_UP_P3 ; 
 int /*<<< orphan*/  netxen_advert_link_change (struct netxen_adapter*,int) ; 

__attribute__((used)) static void netxen_nic_handle_phy_intr(struct netxen_adapter *adapter)
{
	u32 val, port, linkup;

	port = adapter->physical_port;

	if (NX_IS_REVISION_P3(adapter->ahw.revision_id)) {
		val = NXRD32(adapter, CRB_XG_STATE_P3);
		val = XG_LINK_STATE_P3(adapter->ahw.pci_func, val);
		linkup = (val == XG_LINK_UP_P3);
	} else {
		val = NXRD32(adapter, CRB_XG_STATE);
		val = (val >> port*8) & 0xff;
		linkup = (val == XG_LINK_UP);
	}

	netxen_advert_link_change(adapter, linkup);
}