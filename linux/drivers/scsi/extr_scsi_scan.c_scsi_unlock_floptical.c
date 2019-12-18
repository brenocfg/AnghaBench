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
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int MAX_COMMAND_SIZE ; 
 unsigned char MODE_SENSE ; 
 int /*<<< orphan*/  SCSI_TIMEOUT ; 
 int /*<<< orphan*/  scsi_execute_req (struct scsi_device*,unsigned char*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*) ; 

__attribute__((used)) static void scsi_unlock_floptical(struct scsi_device *sdev,
				  unsigned char *result)
{
	unsigned char scsi_cmd[MAX_COMMAND_SIZE];

	sdev_printk(KERN_NOTICE, sdev, "unlocking floptical drive\n");
	scsi_cmd[0] = MODE_SENSE;
	scsi_cmd[1] = 0;
	scsi_cmd[2] = 0x2e;
	scsi_cmd[3] = 0;
	scsi_cmd[4] = 0x2a;     /* size */
	scsi_cmd[5] = 0;
	scsi_execute_req(sdev, scsi_cmd, DMA_FROM_DEVICE, result, 0x2a, NULL,
			 SCSI_TIMEOUT, 3, NULL);
}