#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct MPT3SAS_ADAPTER {int dummy; } ;
struct TYPE_3__ {int RAIDOperation; int /*<<< orphan*/  PercentComplete; int /*<<< orphan*/  VolDevHandle; } ;
typedef  TYPE_1__ Mpi2EventDataIrOperationStatus_t ;

/* Variables and functions */
#define  MPI2_EVENT_IR_RAIDOP_BACKGROUND_INIT 132 
#define  MPI2_EVENT_IR_RAIDOP_CONSISTENCY_CHECK 131 
#define  MPI2_EVENT_IR_RAIDOP_MAKE_DATA_CONSISTENT 130 
#define  MPI2_EVENT_IR_RAIDOP_ONLINE_CAP_EXPANSION 129 
#define  MPI2_EVENT_IR_RAIDOP_RESYNC 128 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_scsih_sas_ir_operation_status_event_debug(struct MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataIrOperationStatus_t *event_data)
{
	char *reason_str = NULL;

	switch (event_data->RAIDOperation) {
	case MPI2_EVENT_IR_RAIDOP_RESYNC:
		reason_str = "resync";
		break;
	case MPI2_EVENT_IR_RAIDOP_ONLINE_CAP_EXPANSION:
		reason_str = "online capacity expansion";
		break;
	case MPI2_EVENT_IR_RAIDOP_CONSISTENCY_CHECK:
		reason_str = "consistency check";
		break;
	case MPI2_EVENT_IR_RAIDOP_BACKGROUND_INIT:
		reason_str = "background init";
		break;
	case MPI2_EVENT_IR_RAIDOP_MAKE_DATA_CONSISTENT:
		reason_str = "make data consistent";
		break;
	}

	if (!reason_str)
		return;

	ioc_info(ioc, "raid operational status: (%s)\thandle(0x%04x), percent complete(%d)\n",
		 reason_str,
		 le16_to_cpu(event_data->VolDevHandle),
		 event_data->PercentComplete);
}