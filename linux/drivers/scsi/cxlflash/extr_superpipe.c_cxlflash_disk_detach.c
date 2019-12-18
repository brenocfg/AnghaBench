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
struct dk_cxlflash_detach {int dummy; } ;

/* Variables and functions */
 int _cxlflash_disk_detach (struct scsi_device*,int /*<<< orphan*/ *,struct dk_cxlflash_detach*) ; 

__attribute__((used)) static int cxlflash_disk_detach(struct scsi_device *sdev,
				struct dk_cxlflash_detach *detach)
{
	return _cxlflash_disk_detach(sdev, NULL, detach);
}