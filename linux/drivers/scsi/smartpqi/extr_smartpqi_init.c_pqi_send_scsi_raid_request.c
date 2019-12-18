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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct pqi_raid_path_request {int /*<<< orphan*/  sg_descriptors; int /*<<< orphan*/  header; } ;
struct pqi_raid_error_info {int dummy; } ;
struct pqi_ctrl_info {int /*<<< orphan*/  pci_dev; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int pqi_build_raid_path_request (struct pqi_ctrl_info*,struct pqi_raid_path_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pqi_pci_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int pqi_submit_raid_request_synchronous (struct pqi_ctrl_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pqi_raid_error_info*,unsigned long) ; 

__attribute__((used)) static int pqi_send_scsi_raid_request(struct pqi_ctrl_info *ctrl_info, u8 cmd,
		u8 *scsi3addr, void *buffer, size_t buffer_length, u16 vpd_page,
		struct pqi_raid_error_info *error_info,
		unsigned long timeout_msecs)
{
	int rc;
	enum dma_data_direction dir;
	struct pqi_raid_path_request request;

	rc = pqi_build_raid_path_request(ctrl_info, &request,
		cmd, scsi3addr, buffer,
		buffer_length, vpd_page, &dir);
	if (rc)
		return rc;

	rc = pqi_submit_raid_request_synchronous(ctrl_info, &request.header,
		 0, error_info, timeout_msecs);

	pqi_pci_unmap(ctrl_info->pci_dev, request.sg_descriptors, 1, dir);
	return rc;
}