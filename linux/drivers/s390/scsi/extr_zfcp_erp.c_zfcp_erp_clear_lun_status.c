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
struct zfcp_scsi_dev {int /*<<< orphan*/  erp_counter; int /*<<< orphan*/  status; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  atomic_andnot (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct zfcp_scsi_dev* sdev_to_zfcp (struct scsi_device*) ; 

void zfcp_erp_clear_lun_status(struct scsi_device *sdev, u32 mask)
{
	struct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	atomic_andnot(mask, &zfcp_sdev->status);

	if (mask & ZFCP_STATUS_COMMON_ERP_FAILED)
		atomic_set(&zfcp_sdev->erp_counter, 0);
}