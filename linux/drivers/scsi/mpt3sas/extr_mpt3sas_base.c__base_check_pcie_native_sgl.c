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
typedef  int /*<<< orphan*/  u16 ;
struct scsi_cmnd {int /*<<< orphan*/  device; } ;
struct _pcie_device {int dummy; } ;
struct MPT3SAS_ADAPTER {int dummy; } ;
typedef  int /*<<< orphan*/  Mpi25SCSIIORequest_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ base_is_prp_possible (struct MPT3SAS_ADAPTER*,struct _pcie_device*,struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  base_make_prp_nvme (struct MPT3SAS_ADAPTER*,struct scsi_cmnd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int scsi_dma_map (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_base_check_pcie_native_sgl(struct MPT3SAS_ADAPTER *ioc,
	Mpi25SCSIIORequest_t *mpi_request, u16 smid, struct scsi_cmnd *scmd,
	struct _pcie_device *pcie_device)
{
	int sges_left;

	/* Get the SG list pointer and info. */
	sges_left = scsi_dma_map(scmd);
	if (sges_left < 0) {
		sdev_printk(KERN_ERR, scmd->device,
			"scsi_dma_map failed: request for %d bytes!\n",
			scsi_bufflen(scmd));
		return 1;
	}

	/* Check if we need to build a native SG list. */
	if (base_is_prp_possible(ioc, pcie_device,
				scmd, sges_left) == 0) {
		/* We built a native SG list, just return. */
		goto out;
	}

	/*
	 * Build native NVMe PRP.
	 */
	base_make_prp_nvme(ioc, scmd, mpi_request,
			smid, sges_left);

	return 0;
out:
	scsi_dma_unmap(scmd);
	return 1;
}