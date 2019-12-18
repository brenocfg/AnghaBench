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
typedef  int /*<<< orphan*/  u64 ;
struct scsi_lun {int dummy; } ;
struct scsi_device {int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,struct scsi_lun*) ; 

__attribute__((used)) static inline u64 zfcp_scsi_dev_lun(struct scsi_device *sdev)
{
	u64 fcp_lun;

	int_to_scsilun(sdev->lun, (struct scsi_lun *)&fcp_lun);
	return fcp_lun;
}