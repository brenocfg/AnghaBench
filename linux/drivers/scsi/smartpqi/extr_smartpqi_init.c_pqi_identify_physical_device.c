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
typedef  void* u8 ;
typedef  int u16 ;
struct pqi_scsi_dev {int /*<<< orphan*/  scsi3addr; } ;
struct pqi_raid_path_request {int /*<<< orphan*/  sg_descriptors; int /*<<< orphan*/  header; void** cdb; } ;
struct pqi_ctrl_info {int /*<<< orphan*/  pci_dev; } ;
struct bmic_identify_physical_device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  BMIC_IDENTIFY_PHYSICAL_DEVICE ; 
 int CISS_GET_DRIVE_NUMBER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_TIMEOUT ; 
 int /*<<< orphan*/  RAID_CTLR_LUNID ; 
 int pqi_build_raid_path_request (struct pqi_ctrl_info*,struct pqi_raid_path_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bmic_identify_physical_device*,size_t,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pqi_pci_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int pqi_submit_raid_request_synchronous (struct pqi_ctrl_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pqi_identify_physical_device(struct pqi_ctrl_info *ctrl_info,
	struct pqi_scsi_dev *device,
	struct bmic_identify_physical_device *buffer,
	size_t buffer_length)
{
	int rc;
	enum dma_data_direction dir;
	u16 bmic_device_index;
	struct pqi_raid_path_request request;

	rc = pqi_build_raid_path_request(ctrl_info, &request,
		BMIC_IDENTIFY_PHYSICAL_DEVICE, RAID_CTLR_LUNID, buffer,
		buffer_length, 0, &dir);
	if (rc)
		return rc;

	bmic_device_index = CISS_GET_DRIVE_NUMBER(device->scsi3addr);
	request.cdb[2] = (u8)bmic_device_index;
	request.cdb[9] = (u8)(bmic_device_index >> 8);

	rc = pqi_submit_raid_request_synchronous(ctrl_info, &request.header,
		0, NULL, NO_TIMEOUT);

	pqi_pci_unmap(ctrl_info->pci_dev, request.sg_descriptors, 1, dir);
	return rc;
}