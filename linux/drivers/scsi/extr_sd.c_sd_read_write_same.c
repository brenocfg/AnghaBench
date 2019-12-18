#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_disk {int ws16; int ws10; struct scsi_device* device; } ;
struct scsi_device {int no_write_same; int no_report_opcodes; TYPE_1__* host; } ;
struct TYPE_2__ {scalar_t__ no_write_same; } ;

/* Variables and functions */
 int /*<<< orphan*/  INQUIRY ; 
 int /*<<< orphan*/  SD_BUF_SIZE ; 
 int /*<<< orphan*/  WRITE_SAME ; 
 int /*<<< orphan*/  WRITE_SAME_16 ; 
 int /*<<< orphan*/  scsi_get_vpd_page (struct scsi_device*,int,unsigned char*,int) ; 
 int scsi_report_opcode (struct scsi_device*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_read_write_same(struct scsi_disk *sdkp, unsigned char *buffer)
{
	struct scsi_device *sdev = sdkp->device;

	if (sdev->host->no_write_same) {
		sdev->no_write_same = 1;

		return;
	}

	if (scsi_report_opcode(sdev, buffer, SD_BUF_SIZE, INQUIRY) < 0) {
		/* too large values might cause issues with arcmsr */
		int vpd_buf_len = 64;

		sdev->no_report_opcodes = 1;

		/* Disable WRITE SAME if REPORT SUPPORTED OPERATION
		 * CODES is unsupported and the device has an ATA
		 * Information VPD page (SAT).
		 */
		if (!scsi_get_vpd_page(sdev, 0x89, buffer, vpd_buf_len))
			sdev->no_write_same = 1;
	}

	if (scsi_report_opcode(sdev, buffer, SD_BUF_SIZE, WRITE_SAME_16) == 1)
		sdkp->ws16 = 1;

	if (scsi_report_opcode(sdev, buffer, SD_BUF_SIZE, WRITE_SAME) == 1)
		sdkp->ws10 = 1;
}