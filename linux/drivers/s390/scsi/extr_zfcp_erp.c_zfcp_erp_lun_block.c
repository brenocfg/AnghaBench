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
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int ZFCP_STATUS_COMMON_UNBLOCKED ; 
 int /*<<< orphan*/  zfcp_erp_clear_lun_status (struct scsi_device*,int) ; 

__attribute__((used)) static void zfcp_erp_lun_block(struct scsi_device *sdev, int clear_mask)
{
	zfcp_erp_clear_lun_status(sdev,
				  ZFCP_STATUS_COMMON_UNBLOCKED | clear_mask);
}