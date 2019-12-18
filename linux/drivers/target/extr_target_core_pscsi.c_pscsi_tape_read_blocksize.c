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
struct se_device {int dummy; } ;
struct scsi_device {int sector_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 int MAX_COMMAND_SIZE ; 
 unsigned char MODE_SENSE ; 
 int get_unaligned_be24 (unsigned char*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int scsi_execute_req (struct scsi_device*,unsigned char*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pscsi_tape_read_blocksize(struct se_device *dev,
		struct scsi_device *sdev)
{
	unsigned char cdb[MAX_COMMAND_SIZE], *buf;
	int ret;

	buf = kzalloc(12, GFP_KERNEL);
	if (!buf)
		goto out_free;

	memset(cdb, 0, MAX_COMMAND_SIZE);
	cdb[0] = MODE_SENSE;
	cdb[4] = 0x0c; /* 12 bytes */

	ret = scsi_execute_req(sdev, cdb, DMA_FROM_DEVICE, buf, 12, NULL,
			HZ, 1, NULL);
	if (ret)
		goto out_free;

	/*
	 * If MODE_SENSE still returns zero, set the default value to 1024.
	 */
	sdev->sector_size = get_unaligned_be24(&buf[9]);
out_free:
	if (!sdev->sector_size)
		sdev->sector_size = 1024;

	kfree(buf);
}