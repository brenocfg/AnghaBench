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
typedef  int /*<<< orphan*/  u64 ;
struct fw_event_work {scalar_t__ event_data; } ;
struct MPT3SAS_ADAPTER {int dummy; } ;
struct TYPE_2__ {int ReasonCode; int /*<<< orphan*/  PhysicalPort; int /*<<< orphan*/  SASAddress; int /*<<< orphan*/  DevHandle; } ;
typedef  TYPE_1__ Mpi25EventDataSasDeviceDiscoveryError_t ;

/* Variables and functions */
#define  MPI25_EVENT_SAS_DISC_ERR_SMP_FAILED 129 
#define  MPI25_EVENT_SAS_DISC_ERR_SMP_TIMEOUT 128 
 int /*<<< orphan*/  ioc_warn (struct MPT3SAS_ADAPTER*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_scsih_sas_device_discovery_error_event(struct MPT3SAS_ADAPTER *ioc,
	struct fw_event_work *fw_event)
{
	Mpi25EventDataSasDeviceDiscoveryError_t *event_data =
		(Mpi25EventDataSasDeviceDiscoveryError_t *)fw_event->event_data;

	switch (event_data->ReasonCode) {
	case MPI25_EVENT_SAS_DISC_ERR_SMP_FAILED:
		ioc_warn(ioc, "SMP command sent to the expander (handle:0x%04x, sas_address:0x%016llx, physical_port:0x%02x) has failed\n",
			 le16_to_cpu(event_data->DevHandle),
			 (u64)le64_to_cpu(event_data->SASAddress),
			 event_data->PhysicalPort);
		break;
	case MPI25_EVENT_SAS_DISC_ERR_SMP_TIMEOUT:
		ioc_warn(ioc, "SMP command sent to the expander (handle:0x%04x, sas_address:0x%016llx, physical_port:0x%02x) has timed out\n",
			 le16_to_cpu(event_data->DevHandle),
			 (u64)le64_to_cpu(event_data->SASAddress),
			 event_data->PhysicalPort);
		break;
	default:
		break;
	}
}