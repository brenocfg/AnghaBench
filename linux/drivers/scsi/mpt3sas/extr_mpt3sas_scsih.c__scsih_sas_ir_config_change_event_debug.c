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
struct MPT3SAS_ADAPTER {int dummy; } ;
struct TYPE_5__ {int NumElements; int /*<<< orphan*/  Flags; int /*<<< orphan*/ * ConfigElement; } ;
struct TYPE_4__ {int ReasonCode; int /*<<< orphan*/  PhysDiskNum; int /*<<< orphan*/  PhysDiskDevHandle; int /*<<< orphan*/  VolDevHandle; int /*<<< orphan*/  ElementFlags; } ;
typedef  TYPE_1__ Mpi2EventIrConfigElement_t ;
typedef  TYPE_2__ Mpi2EventDataIrConfigChangeList_t ;

/* Variables and functions */
 int MPI2_EVENT_IR_CHANGE_EFLAGS_ELEMENT_TYPE_MASK ; 
#define  MPI2_EVENT_IR_CHANGE_EFLAGS_HOTSPARE_ELEMENT 139 
#define  MPI2_EVENT_IR_CHANGE_EFLAGS_VOLPHYSDISK_ELEMENT 138 
#define  MPI2_EVENT_IR_CHANGE_EFLAGS_VOLUME_ELEMENT 137 
 int MPI2_EVENT_IR_CHANGE_FLAGS_FOREIGN_CONFIG ; 
#define  MPI2_EVENT_IR_CHANGE_RC_ADDED 136 
#define  MPI2_EVENT_IR_CHANGE_RC_HIDE 135 
#define  MPI2_EVENT_IR_CHANGE_RC_NO_CHANGE 134 
#define  MPI2_EVENT_IR_CHANGE_RC_PD_CREATED 133 
#define  MPI2_EVENT_IR_CHANGE_RC_PD_DELETED 132 
#define  MPI2_EVENT_IR_CHANGE_RC_REMOVED 131 
#define  MPI2_EVENT_IR_CHANGE_RC_UNHIDE 130 
#define  MPI2_EVENT_IR_CHANGE_RC_VOLUME_CREATED 129 
#define  MPI2_EVENT_IR_CHANGE_RC_VOLUME_DELETED 128 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,char*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,char*,char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_scsih_sas_ir_config_change_event_debug(struct MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataIrConfigChangeList_t *event_data)
{
	Mpi2EventIrConfigElement_t *element;
	u8 element_type;
	int i;
	char *reason_str = NULL, *element_str = NULL;

	element = (Mpi2EventIrConfigElement_t *)&event_data->ConfigElement[0];

	ioc_info(ioc, "raid config change: (%s), elements(%d)\n",
		 le32_to_cpu(event_data->Flags) & MPI2_EVENT_IR_CHANGE_FLAGS_FOREIGN_CONFIG ?
		 "foreign" : "native",
		 event_data->NumElements);
	for (i = 0; i < event_data->NumElements; i++, element++) {
		switch (element->ReasonCode) {
		case MPI2_EVENT_IR_CHANGE_RC_ADDED:
			reason_str = "add";
			break;
		case MPI2_EVENT_IR_CHANGE_RC_REMOVED:
			reason_str = "remove";
			break;
		case MPI2_EVENT_IR_CHANGE_RC_NO_CHANGE:
			reason_str = "no change";
			break;
		case MPI2_EVENT_IR_CHANGE_RC_HIDE:
			reason_str = "hide";
			break;
		case MPI2_EVENT_IR_CHANGE_RC_UNHIDE:
			reason_str = "unhide";
			break;
		case MPI2_EVENT_IR_CHANGE_RC_VOLUME_CREATED:
			reason_str = "volume_created";
			break;
		case MPI2_EVENT_IR_CHANGE_RC_VOLUME_DELETED:
			reason_str = "volume_deleted";
			break;
		case MPI2_EVENT_IR_CHANGE_RC_PD_CREATED:
			reason_str = "pd_created";
			break;
		case MPI2_EVENT_IR_CHANGE_RC_PD_DELETED:
			reason_str = "pd_deleted";
			break;
		default:
			reason_str = "unknown reason";
			break;
		}
		element_type = le16_to_cpu(element->ElementFlags) &
		    MPI2_EVENT_IR_CHANGE_EFLAGS_ELEMENT_TYPE_MASK;
		switch (element_type) {
		case MPI2_EVENT_IR_CHANGE_EFLAGS_VOLUME_ELEMENT:
			element_str = "volume";
			break;
		case MPI2_EVENT_IR_CHANGE_EFLAGS_VOLPHYSDISK_ELEMENT:
			element_str = "phys disk";
			break;
		case MPI2_EVENT_IR_CHANGE_EFLAGS_HOTSPARE_ELEMENT:
			element_str = "hot spare";
			break;
		default:
			element_str = "unknown element";
			break;
		}
		pr_info("\t(%s:%s), vol handle(0x%04x), " \
		    "pd handle(0x%04x), pd num(0x%02x)\n", element_str,
		    reason_str, le16_to_cpu(element->VolDevHandle),
		    le16_to_cpu(element->PhysDiskDevHandle),
		    element->PhysDiskNum);
	}
}