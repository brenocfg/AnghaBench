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
struct scsi_device {int no_uld_attach; } ;

/* Variables and functions */
 int scsi_device_reprobe (struct scsi_device*) ; 

__attribute__((used)) static void
mptsas_reprobe_lun(struct scsi_device *sdev, void *data)
{
	int rc;

	sdev->no_uld_attach = data ? 1 : 0;
	rc = scsi_device_reprobe(sdev);
}