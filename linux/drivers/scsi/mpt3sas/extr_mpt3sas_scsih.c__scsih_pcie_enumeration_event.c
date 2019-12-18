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
struct fw_event_work {scalar_t__ event_data; } ;
struct MPT3SAS_ADAPTER {int logging_level; } ;
struct TYPE_2__ {scalar_t__ ReasonCode; scalar_t__ EnumerationStatus; int /*<<< orphan*/  Flags; } ;
typedef  TYPE_1__ Mpi26EventDataPCIeEnumeration_t ;

/* Variables and functions */
 scalar_t__ MPI26_EVENT_PCIE_ENUM_RC_STARTED ; 
 int MPT_DEBUG_EVENT_WORK_TASK ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static void
_scsih_pcie_enumeration_event(struct MPT3SAS_ADAPTER *ioc,
	struct fw_event_work *fw_event)
{
	Mpi26EventDataPCIeEnumeration_t *event_data =
		(Mpi26EventDataPCIeEnumeration_t *)fw_event->event_data;

	if (!(ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK))
		return;

	ioc_info(ioc, "pcie enumeration event: (%s) Flag 0x%02x",
		 (event_data->ReasonCode == MPI26_EVENT_PCIE_ENUM_RC_STARTED) ?
		 "started" : "completed",
		 event_data->Flags);
	if (event_data->EnumerationStatus)
		pr_cont("enumeration_status(0x%08x)",
			le32_to_cpu(event_data->EnumerationStatus));
	pr_cont("\n");
}