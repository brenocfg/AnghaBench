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
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {void* status; } ;
struct MPT3SAS_ADAPTER {int remove_host; scalar_t__ is_driver_loading; scalar_t__ wait_for_discovery_to_complete; TYPE_1__ port_enable_cmds; scalar_t__ start_scan_failed; scalar_t__ start_scan; } ;

/* Variables and functions */
 int HZ ; 
 void* MPT3_CMD_NOT_USED ; 
 int /*<<< orphan*/  _scsih_probe_devices (struct MPT3SAS_ADAPTER*) ; 
 scalar_t__ disable_discovery ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,...) ; 
 int /*<<< orphan*/  mpt3sas_base_start_watchdog (struct MPT3SAS_ADAPTER*) ; 
 struct MPT3SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int
scsih_scan_finished(struct Scsi_Host *shost, unsigned long time)
{
	struct MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	if (disable_discovery > 0) {
		ioc->is_driver_loading = 0;
		ioc->wait_for_discovery_to_complete = 0;
		return 1;
	}

	if (time >= (300 * HZ)) {
		ioc->port_enable_cmds.status = MPT3_CMD_NOT_USED;
		ioc_info(ioc, "port enable: FAILED with timeout (timeout=300s)\n");
		ioc->is_driver_loading = 0;
		return 1;
	}

	if (ioc->start_scan)
		return 0;

	if (ioc->start_scan_failed) {
		ioc_info(ioc, "port enable: FAILED with (ioc_status=0x%08x)\n",
			 ioc->start_scan_failed);
		ioc->is_driver_loading = 0;
		ioc->wait_for_discovery_to_complete = 0;
		ioc->remove_host = 1;
		return 1;
	}

	ioc_info(ioc, "port enable: SUCCESS\n");
	ioc->port_enable_cmds.status = MPT3_CMD_NOT_USED;

	if (ioc->wait_for_discovery_to_complete) {
		ioc->wait_for_discovery_to_complete = 0;
		_scsih_probe_devices(ioc);
	}
	mpt3sas_base_start_watchdog(ioc);
	ioc->is_driver_loading = 0;
	return 1;
}