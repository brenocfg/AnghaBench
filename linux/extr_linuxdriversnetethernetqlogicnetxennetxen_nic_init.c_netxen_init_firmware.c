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
struct TYPE_2__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {TYPE_1__ ahw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRB_CMDPEG_STATE ; 
 int /*<<< orphan*/  CRB_MPORT_MODE ; 
 int /*<<< orphan*/  CRB_NIC_CAPABILITIES_HOST ; 
 int /*<<< orphan*/  CRB_NIC_MSI_MODE_HOST ; 
 int /*<<< orphan*/  INTR_SCHEME_PERPORT ; 
 int /*<<< orphan*/  MPORT_MULTI_FUNCTION_MODE ; 
 int /*<<< orphan*/  MSI_MODE_MULTIFUNC ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NX_IS_REVISION_P2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHAN_INITIALIZE_ACK ; 
 int netxen_receive_peg_ready (struct netxen_adapter*) ; 

int netxen_init_firmware(struct netxen_adapter *adapter)
{
	int err;

	err = netxen_receive_peg_ready(adapter);
	if (err)
		return err;

	NXWR32(adapter, CRB_NIC_CAPABILITIES_HOST, INTR_SCHEME_PERPORT);
	NXWR32(adapter, CRB_MPORT_MODE, MPORT_MULTI_FUNCTION_MODE);
	NXWR32(adapter, CRB_CMDPEG_STATE, PHAN_INITIALIZE_ACK);

	if (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		NXWR32(adapter, CRB_NIC_MSI_MODE_HOST, MSI_MODE_MULTIFUNC);

	return err;
}