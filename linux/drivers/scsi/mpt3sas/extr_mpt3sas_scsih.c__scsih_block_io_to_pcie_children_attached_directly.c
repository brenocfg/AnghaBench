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
typedef  scalar_t__ u16 ;
struct MPT3SAS_ADAPTER {int dummy; } ;
struct TYPE_5__ {int NumEntries; TYPE_1__* PortEntry; } ;
struct TYPE_4__ {scalar_t__ PortStatus; int /*<<< orphan*/  AttachedDevHandle; } ;
typedef  TYPE_2__ Mpi26EventDataPCIeTopologyChangeList_t ;

/* Variables and functions */
 scalar_t__ MPI26_EVENT_PCIE_TOPO_PS_DELAY_NOT_RESPONDING ; 
 int /*<<< orphan*/  _scsih_block_io_device (struct MPT3SAS_ADAPTER*,scalar_t__) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_scsih_block_io_to_pcie_children_attached_directly(struct MPT3SAS_ADAPTER *ioc,
		Mpi26EventDataPCIeTopologyChangeList_t *event_data)
{
	int i;
	u16 handle;
	u16 reason_code;

	for (i = 0; i < event_data->NumEntries; i++) {
		handle =
			le16_to_cpu(event_data->PortEntry[i].AttachedDevHandle);
		if (!handle)
			continue;
		reason_code = event_data->PortEntry[i].PortStatus;
		if (reason_code ==
				MPI26_EVENT_PCIE_TOPO_PS_DELAY_NOT_RESPONDING)
			_scsih_block_io_device(ioc, handle);
	}
}