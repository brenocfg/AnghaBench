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
struct TYPE_5__ {int ExpStatus; int StartPhyNum; int NumEntries; TYPE_1__* PHY; int /*<<< orphan*/  EnclosureHandle; int /*<<< orphan*/  ExpanderDevHandle; } ;
struct TYPE_4__ {int PhyStatus; int LinkRate; int /*<<< orphan*/  AttachedDevHandle; } ;
typedef  TYPE_2__ Mpi2EventDataSasTopologyChangeList_t ;

/* Variables and functions */
#define  MPI2_EVENT_SAS_TOPO_ES_ADDED 136 
#define  MPI2_EVENT_SAS_TOPO_ES_DELAY_NOT_RESPONDING 135 
#define  MPI2_EVENT_SAS_TOPO_ES_NOT_RESPONDING 134 
#define  MPI2_EVENT_SAS_TOPO_ES_RESPONDING 133 
#define  MPI2_EVENT_SAS_TOPO_RC_DELAY_NOT_RESPONDING 132 
 int MPI2_EVENT_SAS_TOPO_RC_MASK ; 
#define  MPI2_EVENT_SAS_TOPO_RC_NO_CHANGE 131 
#define  MPI2_EVENT_SAS_TOPO_RC_PHY_CHANGED 130 
#define  MPI2_EVENT_SAS_TOPO_RC_TARG_ADDED 129 
#define  MPI2_EVENT_SAS_TOPO_RC_TARG_NOT_RESPONDING 128 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,char*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int,int,...) ; 

__attribute__((used)) static void
_scsih_sas_topology_change_event_debug(struct MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataSasTopologyChangeList_t *event_data)
{
	int i;
	u16 handle;
	u16 reason_code;
	u8 phy_number;
	char *status_str = NULL;
	u8 link_rate, prev_link_rate;

	switch (event_data->ExpStatus) {
	case MPI2_EVENT_SAS_TOPO_ES_ADDED:
		status_str = "add";
		break;
	case MPI2_EVENT_SAS_TOPO_ES_NOT_RESPONDING:
		status_str = "remove";
		break;
	case MPI2_EVENT_SAS_TOPO_ES_RESPONDING:
	case 0:
		status_str =  "responding";
		break;
	case MPI2_EVENT_SAS_TOPO_ES_DELAY_NOT_RESPONDING:
		status_str = "remove delay";
		break;
	default:
		status_str = "unknown status";
		break;
	}
	ioc_info(ioc, "sas topology change: (%s)\n", status_str);
	pr_info("\thandle(0x%04x), enclosure_handle(0x%04x) " \
	    "start_phy(%02d), count(%d)\n",
	    le16_to_cpu(event_data->ExpanderDevHandle),
	    le16_to_cpu(event_data->EnclosureHandle),
	    event_data->StartPhyNum, event_data->NumEntries);
	for (i = 0; i < event_data->NumEntries; i++) {
		handle = le16_to_cpu(event_data->PHY[i].AttachedDevHandle);
		if (!handle)
			continue;
		phy_number = event_data->StartPhyNum + i;
		reason_code = event_data->PHY[i].PhyStatus &
		    MPI2_EVENT_SAS_TOPO_RC_MASK;
		switch (reason_code) {
		case MPI2_EVENT_SAS_TOPO_RC_TARG_ADDED:
			status_str = "target add";
			break;
		case MPI2_EVENT_SAS_TOPO_RC_TARG_NOT_RESPONDING:
			status_str = "target remove";
			break;
		case MPI2_EVENT_SAS_TOPO_RC_DELAY_NOT_RESPONDING:
			status_str = "delay target remove";
			break;
		case MPI2_EVENT_SAS_TOPO_RC_PHY_CHANGED:
			status_str = "link rate change";
			break;
		case MPI2_EVENT_SAS_TOPO_RC_NO_CHANGE:
			status_str = "target responding";
			break;
		default:
			status_str = "unknown";
			break;
		}
		link_rate = event_data->PHY[i].LinkRate >> 4;
		prev_link_rate = event_data->PHY[i].LinkRate & 0xF;
		pr_info("\tphy(%02d), attached_handle(0x%04x): %s:" \
		    " link rate: new(0x%02x), old(0x%02x)\n", phy_number,
		    handle, status_str, link_rate, prev_link_rate);

	}
}