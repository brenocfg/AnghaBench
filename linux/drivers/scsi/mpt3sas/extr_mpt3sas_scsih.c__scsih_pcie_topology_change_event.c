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
typedef  int u8 ;
typedef  int u16 ;
struct fw_event_work {scalar_t__ ignore; scalar_t__ event_data; } ;
struct _pcie_device {int dummy; } ;
struct MPT3SAS_ADAPTER {int logging_level; scalar_t__ shost_recovery; int /*<<< orphan*/  pend_os_device_add; int /*<<< orphan*/  pcie_device_lock; scalar_t__ pci_error_recovery; scalar_t__ remove_host; } ;
struct TYPE_5__ {int NumEntries; TYPE_1__* PortEntry; } ;
struct TYPE_4__ {int PortStatus; int CurrentPortInfo; int PreviousPortInfo; int /*<<< orphan*/  AttachedDevHandle; } ;
typedef  TYPE_2__ Mpi26EventDataPCIeTopologyChangeList_t ;

/* Variables and functions */
 int MPI26_EVENT_PCIE_TOPO_PI_RATE_2_5 ; 
 int MPI26_EVENT_PCIE_TOPO_PI_RATE_MASK ; 
#define  MPI26_EVENT_PCIE_TOPO_PS_DEV_ADDED 130 
#define  MPI26_EVENT_PCIE_TOPO_PS_NOT_RESPONDING 129 
 int MPI26_EVENT_PCIE_TOPO_PS_NO_CHANGE ; 
#define  MPI26_EVENT_PCIE_TOPO_PS_PORT_CHANGED 128 
 int MPT_DEBUG_EVENT_WORK_TASK ; 
 struct _pcie_device* __mpt3sas_get_pdev_by_handle (struct MPT3SAS_ADAPTER*,int) ; 
 int _scsih_pcie_add_device (struct MPT3SAS_ADAPTER*,int) ; 
 int /*<<< orphan*/  _scsih_pcie_check_device (struct MPT3SAS_ADAPTER*,int) ; 
 int /*<<< orphan*/  _scsih_pcie_device_remove_by_handle (struct MPT3SAS_ADAPTER*,int) ; 
 int /*<<< orphan*/  _scsih_pcie_topology_change_event_debug (struct MPT3SAS_ADAPTER*,TYPE_2__*) ; 
 int /*<<< orphan*/  dewtprintk (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_device_put (struct _pcie_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_scsih_pcie_topology_change_event(struct MPT3SAS_ADAPTER *ioc,
	struct fw_event_work *fw_event)
{
	int i;
	u16 handle;
	u16 reason_code;
	u8 link_rate, prev_link_rate;
	unsigned long flags;
	int rc;
	Mpi26EventDataPCIeTopologyChangeList_t *event_data =
		(Mpi26EventDataPCIeTopologyChangeList_t *) fw_event->event_data;
	struct _pcie_device *pcie_device;

	if (ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK)
		_scsih_pcie_topology_change_event_debug(ioc, event_data);

	if (ioc->shost_recovery || ioc->remove_host ||
		ioc->pci_error_recovery)
		return;

	if (fw_event->ignore) {
		dewtprintk(ioc, ioc_info(ioc, "ignoring switch event\n"));
		return;
	}

	/* handle siblings events */
	for (i = 0; i < event_data->NumEntries; i++) {
		if (fw_event->ignore) {
			dewtprintk(ioc,
				   ioc_info(ioc, "ignoring switch event\n"));
			return;
		}
		if (ioc->remove_host || ioc->pci_error_recovery)
			return;
		reason_code = event_data->PortEntry[i].PortStatus;
		handle =
			le16_to_cpu(event_data->PortEntry[i].AttachedDevHandle);
		if (!handle)
			continue;

		link_rate = event_data->PortEntry[i].CurrentPortInfo
			& MPI26_EVENT_PCIE_TOPO_PI_RATE_MASK;
		prev_link_rate = event_data->PortEntry[i].PreviousPortInfo
			& MPI26_EVENT_PCIE_TOPO_PI_RATE_MASK;

		switch (reason_code) {
		case MPI26_EVENT_PCIE_TOPO_PS_PORT_CHANGED:
			if (ioc->shost_recovery)
				break;
			if (link_rate == prev_link_rate)
				break;
			if (link_rate < MPI26_EVENT_PCIE_TOPO_PI_RATE_2_5)
				break;

			_scsih_pcie_check_device(ioc, handle);

			/* This code after this point handles the test case
			 * where a device has been added, however its returning
			 * BUSY for sometime.  Then before the Device Missing
			 * Delay expires and the device becomes READY, the
			 * device is removed and added back.
			 */
			spin_lock_irqsave(&ioc->pcie_device_lock, flags);
			pcie_device = __mpt3sas_get_pdev_by_handle(ioc, handle);
			spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);

			if (pcie_device) {
				pcie_device_put(pcie_device);
				break;
			}

			if (!test_bit(handle, ioc->pend_os_device_add))
				break;

			dewtprintk(ioc,
				   ioc_info(ioc, "handle(0x%04x) device not found: convert event to a device add\n",
					    handle));
			event_data->PortEntry[i].PortStatus &= 0xF0;
			event_data->PortEntry[i].PortStatus |=
				MPI26_EVENT_PCIE_TOPO_PS_DEV_ADDED;
			/* fall through */
		case MPI26_EVENT_PCIE_TOPO_PS_DEV_ADDED:
			if (ioc->shost_recovery)
				break;
			if (link_rate < MPI26_EVENT_PCIE_TOPO_PI_RATE_2_5)
				break;

			rc = _scsih_pcie_add_device(ioc, handle);
			if (!rc) {
				/* mark entry vacant */
				/* TODO This needs to be reviewed and fixed,
				 * we dont have an entry
				 * to make an event void like vacant
				 */
				event_data->PortEntry[i].PortStatus |=
					MPI26_EVENT_PCIE_TOPO_PS_NO_CHANGE;
			}
			break;
		case MPI26_EVENT_PCIE_TOPO_PS_NOT_RESPONDING:
			_scsih_pcie_device_remove_by_handle(ioc, handle);
			break;
		}
	}
}