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
struct scsi_cmnd {int* cmnd; } ;
struct MPT3SAS_ADAPTER {scalar_t__ hba_mpi_version_belonged; scalar_t__ remove_host; scalar_t__ pci_error_recovery; } ;

/* Variables and functions */
 scalar_t__ MPI2_VERSION ; 
#define  START_STOP 129 
#define  SYNCHRONIZE_CACHE 128 

inline bool _scsih_allow_scmd_to_device(struct MPT3SAS_ADAPTER *ioc,
	struct scsi_cmnd *scmd)
{

	if (ioc->pci_error_recovery)
		return false;

	if (ioc->hba_mpi_version_belonged == MPI2_VERSION) {
		if (ioc->remove_host)
			return false;

		return true;
	}

	if (ioc->remove_host) {

		switch (scmd->cmnd[0]) {
		case SYNCHRONIZE_CACHE:
		case START_STOP:
			return true;
		default:
			return false;
		}
	}

	return true;
}