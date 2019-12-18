#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fw_event_work {int event; scalar_t__ event_data; int /*<<< orphan*/  device_handle; } ;
struct SL_WH_TRIGGERS_EVENT_DATA_T {int dummy; } ;
struct MPT3SAS_ADAPTER {int logging_level; int /*<<< orphan*/  start_scan; scalar_t__ remove_host; int /*<<< orphan*/  shost_recovery; int /*<<< orphan*/  shost; scalar_t__ pci_error_recovery; } ;
typedef  int /*<<< orphan*/  Mpi2EventDataSasDeviceStatusChange_t ;

/* Variables and functions */
#define  MPI2_EVENT_IR_CONFIGURATION_CHANGE_LIST 144 
#define  MPI2_EVENT_IR_OPERATION_STATUS 143 
#define  MPI2_EVENT_IR_PHYSICAL_DISK 142 
#define  MPI2_EVENT_IR_VOLUME 141 
#define  MPI2_EVENT_PCIE_DEVICE_STATUS_CHANGE 140 
#define  MPI2_EVENT_PCIE_ENUMERATION 139 
#define  MPI2_EVENT_PCIE_TOPOLOGY_CHANGE_LIST 138 
#define  MPI2_EVENT_SAS_BROADCAST_PRIMITIVE 137 
#define  MPI2_EVENT_SAS_DEVICE_DISCOVERY_ERROR 136 
#define  MPI2_EVENT_SAS_DEVICE_STATUS_CHANGE 135 
#define  MPI2_EVENT_SAS_DISCOVERY 134 
#define  MPI2_EVENT_SAS_ENCL_DEVICE_STATUS_CHANGE 133 
#define  MPI2_EVENT_SAS_TOPOLOGY_CHANGE_LIST 132 
#define  MPT3SAS_PORT_ENABLE_COMPLETE 131 
#define  MPT3SAS_PROCESS_TRIGGER_DIAG 130 
#define  MPT3SAS_REMOVE_UNRESPONDING_DEVICES 129 
#define  MPT3SAS_TURN_ON_PFA_LED 128 
 int MPT_DEBUG_EVENT_WORK_TASK ; 
 int /*<<< orphan*/  _scsih_fw_event_del_from_list (struct MPT3SAS_ADAPTER*,struct fw_event_work*) ; 
 int /*<<< orphan*/  _scsih_pcie_device_status_change_event (struct MPT3SAS_ADAPTER*,struct fw_event_work*) ; 
 int /*<<< orphan*/  _scsih_pcie_enumeration_event (struct MPT3SAS_ADAPTER*,struct fw_event_work*) ; 
 int /*<<< orphan*/  _scsih_pcie_topology_change_event (struct MPT3SAS_ADAPTER*,struct fw_event_work*) ; 
 int /*<<< orphan*/  _scsih_remove_unresponding_devices (struct MPT3SAS_ADAPTER*) ; 
 int /*<<< orphan*/  _scsih_sas_broadcast_primitive_event (struct MPT3SAS_ADAPTER*,struct fw_event_work*) ; 
 int /*<<< orphan*/  _scsih_sas_device_discovery_error_event (struct MPT3SAS_ADAPTER*,struct fw_event_work*) ; 
 int /*<<< orphan*/  _scsih_sas_device_status_change_event_debug (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _scsih_sas_discovery_event (struct MPT3SAS_ADAPTER*,struct fw_event_work*) ; 
 int /*<<< orphan*/  _scsih_sas_enclosure_dev_status_change_event (struct MPT3SAS_ADAPTER*,struct fw_event_work*) ; 
 int /*<<< orphan*/  _scsih_sas_ir_config_change_event (struct MPT3SAS_ADAPTER*,struct fw_event_work*) ; 
 int /*<<< orphan*/  _scsih_sas_ir_operation_status_event (struct MPT3SAS_ADAPTER*,struct fw_event_work*) ; 
 int /*<<< orphan*/  _scsih_sas_ir_physical_disk_event (struct MPT3SAS_ADAPTER*,struct fw_event_work*) ; 
 int /*<<< orphan*/  _scsih_sas_ir_volume_event (struct MPT3SAS_ADAPTER*,struct fw_event_work*) ; 
 int /*<<< orphan*/  _scsih_sas_topology_change_event (struct MPT3SAS_ADAPTER*,struct fw_event_work*) ; 
 int /*<<< orphan*/  _scsih_scan_for_devices_after_reset (struct MPT3SAS_ADAPTER*) ; 
 int /*<<< orphan*/  _scsih_turn_on_pfa_led (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dewtprintk (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_event_work_put (struct fw_event_work*) ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*) ; 
 int* missing_delay ; 
 int /*<<< orphan*/  mpt3sas_base_update_missing_delay (struct MPT3SAS_ADAPTER*,int,int) ; 
 int /*<<< orphan*/  mpt3sas_process_trigger_data (struct MPT3SAS_ADAPTER*,struct SL_WH_TRIGGERS_EVENT_DATA_T*) ; 
 int /*<<< orphan*/  scsi_host_in_recovery (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssleep (int) ; 

__attribute__((used)) static void
_mpt3sas_fw_work(struct MPT3SAS_ADAPTER *ioc, struct fw_event_work *fw_event)
{
	_scsih_fw_event_del_from_list(ioc, fw_event);

	/* the queue is being flushed so ignore this event */
	if (ioc->remove_host || ioc->pci_error_recovery) {
		fw_event_work_put(fw_event);
		return;
	}

	switch (fw_event->event) {
	case MPT3SAS_PROCESS_TRIGGER_DIAG:
		mpt3sas_process_trigger_data(ioc,
			(struct SL_WH_TRIGGERS_EVENT_DATA_T *)
			fw_event->event_data);
		break;
	case MPT3SAS_REMOVE_UNRESPONDING_DEVICES:
		while (scsi_host_in_recovery(ioc->shost) ||
					 ioc->shost_recovery) {
			/*
			 * If we're unloading, bail. Otherwise, this can become
			 * an infinite loop.
			 */
			if (ioc->remove_host)
				goto out;
			ssleep(1);
		}
		_scsih_remove_unresponding_devices(ioc);
		_scsih_scan_for_devices_after_reset(ioc);
		break;
	case MPT3SAS_PORT_ENABLE_COMPLETE:
		ioc->start_scan = 0;
		if (missing_delay[0] != -1 && missing_delay[1] != -1)
			mpt3sas_base_update_missing_delay(ioc, missing_delay[0],
			    missing_delay[1]);
		dewtprintk(ioc,
			   ioc_info(ioc, "port enable: complete from worker thread\n"));
		break;
	case MPT3SAS_TURN_ON_PFA_LED:
		_scsih_turn_on_pfa_led(ioc, fw_event->device_handle);
		break;
	case MPI2_EVENT_SAS_TOPOLOGY_CHANGE_LIST:
		_scsih_sas_topology_change_event(ioc, fw_event);
		break;
	case MPI2_EVENT_SAS_DEVICE_STATUS_CHANGE:
		if (ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK)
			_scsih_sas_device_status_change_event_debug(ioc,
			    (Mpi2EventDataSasDeviceStatusChange_t *)
			    fw_event->event_data);
		break;
	case MPI2_EVENT_SAS_DISCOVERY:
		_scsih_sas_discovery_event(ioc, fw_event);
		break;
	case MPI2_EVENT_SAS_DEVICE_DISCOVERY_ERROR:
		_scsih_sas_device_discovery_error_event(ioc, fw_event);
		break;
	case MPI2_EVENT_SAS_BROADCAST_PRIMITIVE:
		_scsih_sas_broadcast_primitive_event(ioc, fw_event);
		break;
	case MPI2_EVENT_SAS_ENCL_DEVICE_STATUS_CHANGE:
		_scsih_sas_enclosure_dev_status_change_event(ioc,
		    fw_event);
		break;
	case MPI2_EVENT_IR_CONFIGURATION_CHANGE_LIST:
		_scsih_sas_ir_config_change_event(ioc, fw_event);
		break;
	case MPI2_EVENT_IR_VOLUME:
		_scsih_sas_ir_volume_event(ioc, fw_event);
		break;
	case MPI2_EVENT_IR_PHYSICAL_DISK:
		_scsih_sas_ir_physical_disk_event(ioc, fw_event);
		break;
	case MPI2_EVENT_IR_OPERATION_STATUS:
		_scsih_sas_ir_operation_status_event(ioc, fw_event);
		break;
	case MPI2_EVENT_PCIE_DEVICE_STATUS_CHANGE:
		_scsih_pcie_device_status_change_event(ioc, fw_event);
		break;
	case MPI2_EVENT_PCIE_ENUMERATION:
		_scsih_pcie_enumeration_event(ioc, fw_event);
		break;
	case MPI2_EVENT_PCIE_TOPOLOGY_CHANGE_LIST:
		_scsih_pcie_topology_change_event(ioc, fw_event);
			return;
	break;
	}
out:
	fw_event_work_put(fw_event);
}