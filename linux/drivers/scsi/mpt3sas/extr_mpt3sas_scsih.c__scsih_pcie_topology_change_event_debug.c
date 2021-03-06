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
struct MPT3SAS_ADAPTER {int dummy; } ;
struct TYPE_5__ {int SwitchStatus; int StartPortNum; int NumEntries; TYPE_1__* PortEntry; int /*<<< orphan*/  EnclosureHandle; int /*<<< orphan*/  SwitchDevHandle; } ;
struct TYPE_4__ {int PortStatus; int CurrentPortInfo; int PreviousPortInfo; int /*<<< orphan*/  AttachedDevHandle; } ;
typedef  TYPE_2__ Mpi26EventDataPCIeTopologyChangeList_t ;

/* Variables and functions */
 int MPI26_EVENT_PCIE_TOPO_PI_RATE_MASK ; 
#define  MPI26_EVENT_PCIE_TOPO_PS_DELAY_NOT_RESPONDING 136 
#define  MPI26_EVENT_PCIE_TOPO_PS_DEV_ADDED 135 
#define  MPI26_EVENT_PCIE_TOPO_PS_NOT_RESPONDING 134 
#define  MPI26_EVENT_PCIE_TOPO_PS_NO_CHANGE 133 
#define  MPI26_EVENT_PCIE_TOPO_PS_PORT_CHANGED 132 
#define  MPI26_EVENT_PCIE_TOPO_SS_ADDED 131 
#define  MPI26_EVENT_PCIE_TOPO_SS_DELAY_NOT_RESPONDING 130 
#define  MPI26_EVENT_PCIE_TOPO_SS_NOT_RESPONDING 129 
#define  MPI26_EVENT_PCIE_TOPO_SS_RESPONDING 128 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,char*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int,int,...) ; 

__attribute__((used)) static void
_scsih_pcie_topology_change_event_debug(struct MPT3SAS_ADAPTER *ioc,
	Mpi26EventDataPCIeTopologyChangeList_t *event_data)
{
	int i;
	u16 handle;
	u16 reason_code;
	u8 port_number;
	char *status_str = NULL;
	u8 link_rate, prev_link_rate;

	switch (event_data->SwitchStatus) {
	case MPI26_EVENT_PCIE_TOPO_SS_ADDED:
		status_str = "add";
		break;
	case MPI26_EVENT_PCIE_TOPO_SS_NOT_RESPONDING:
		status_str = "remove";
		break;
	case MPI26_EVENT_PCIE_TOPO_SS_RESPONDING:
	case 0:
		status_str =  "responding";
		break;
	case MPI26_EVENT_PCIE_TOPO_SS_DELAY_NOT_RESPONDING:
		status_str = "remove delay";
		break;
	default:
		status_str = "unknown status";
		break;
	}
	ioc_info(ioc, "pcie topology change: (%s)\n", status_str);
	pr_info("\tswitch_handle(0x%04x), enclosure_handle(0x%04x)"
		"start_port(%02d), count(%d)\n",
		le16_to_cpu(event_data->SwitchDevHandle),
		le16_to_cpu(event_data->EnclosureHandle),
		event_data->StartPortNum, event_data->NumEntries);
	for (i = 0; i < event_data->NumEntries; i++) {
		handle =
			le16_to_cpu(event_data->PortEntry[i].AttachedDevHandle);
		if (!handle)
			continue;
		port_number = event_data->StartPortNum + i;
		reason_code = event_data->PortEntry[i].PortStatus;
		switch (reason_code) {
		case MPI26_EVENT_PCIE_TOPO_PS_DEV_ADDED:
			status_str = "target add";
			break;
		case MPI26_EVENT_PCIE_TOPO_PS_NOT_RESPONDING:
			status_str = "target remove";
			break;
		case MPI26_EVENT_PCIE_TOPO_PS_DELAY_NOT_RESPONDING:
			status_str = "delay target remove";
			break;
		case MPI26_EVENT_PCIE_TOPO_PS_PORT_CHANGED:
			status_str = "link rate change";
			break;
		case MPI26_EVENT_PCIE_TOPO_PS_NO_CHANGE:
			status_str = "target responding";
			break;
		default:
			status_str = "unknown";
			break;
		}
		link_rate = event_data->PortEntry[i].CurrentPortInfo &
			MPI26_EVENT_PCIE_TOPO_PI_RATE_MASK;
		prev_link_rate = event_data->PortEntry[i].PreviousPortInfo &
			MPI26_EVENT_PCIE_TOPO_PI_RATE_MASK;
		pr_info("\tport(%02d), attached_handle(0x%04x): %s:"
			" link rate: new(0x%02x), old(0x%02x)\n", port_number,
			handle, status_str, link_rate, prev_link_rate);
	}
}