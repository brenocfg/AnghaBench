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
typedef  int u32 ;
struct scsi_cmnd {int dummy; } ;
struct _pcie_device {int /*<<< orphan*/  device_info; } ;
struct MPT3SAS_ADAPTER {int dummy; } ;

/* Variables and functions */
 int NVME_PRP_PAGE_SIZE ; 
 scalar_t__ mpt3sas_scsih_is_pcie_scsi_device (int /*<<< orphan*/ ) ; 
 int scsi_bufflen (struct scsi_cmnd*) ; 

__attribute__((used)) static bool
base_is_prp_possible(struct MPT3SAS_ADAPTER *ioc,
	struct _pcie_device *pcie_device, struct scsi_cmnd *scmd, int sge_count)
{
	u32 data_length = 0;
	bool build_prp = true;

	data_length = scsi_bufflen(scmd);
	if (pcie_device &&
	    (mpt3sas_scsih_is_pcie_scsi_device(pcie_device->device_info))) {
		build_prp = false;
		return build_prp;
	}

	/* If Datalenth is <= 16K and number of SGE’s entries are <= 2
	 * we built IEEE SGL
	 */
	if ((data_length <= NVME_PRP_PAGE_SIZE*4) && (sge_count <= 2))
		build_prp = false;

	return build_prp;
}