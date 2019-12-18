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
typedef  int /*<<< orphan*/  u64 ;
struct MPT3SAS_ADAPTER {int dummy; } ;
struct TYPE_3__ {int ReasonCode; int /*<<< orphan*/  StartSlot; int /*<<< orphan*/  EnclosureLogicalID; int /*<<< orphan*/  EnclosureHandle; } ;
typedef  TYPE_1__ Mpi2EventDataSasEnclDevStatusChange_t ;

/* Variables and functions */
#define  MPI2_EVENT_SAS_ENCL_RC_ADDED 129 
#define  MPI2_EVENT_SAS_ENCL_RC_NOT_RESPONDING 128 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_scsih_sas_enclosure_dev_status_change_event_debug(struct MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataSasEnclDevStatusChange_t *event_data)
{
	char *reason_str = NULL;

	switch (event_data->ReasonCode) {
	case MPI2_EVENT_SAS_ENCL_RC_ADDED:
		reason_str = "enclosure add";
		break;
	case MPI2_EVENT_SAS_ENCL_RC_NOT_RESPONDING:
		reason_str = "enclosure remove";
		break;
	default:
		reason_str = "unknown reason";
		break;
	}

	ioc_info(ioc, "enclosure status change: (%s)\n"
		 "\thandle(0x%04x), enclosure logical id(0x%016llx) number slots(%d)\n",
		 reason_str,
		 le16_to_cpu(event_data->EnclosureHandle),
		 (u64)le64_to_cpu(event_data->EnclosureLogicalID),
		 le16_to_cpu(event_data->StartSlot));
}