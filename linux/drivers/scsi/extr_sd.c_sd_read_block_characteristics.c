#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct scsi_disk {unsigned char zoned; scalar_t__ first_scan; TYPE_3__* device; TYPE_1__* disk; } ;
struct TYPE_5__ {scalar_t__ zoned; } ;
struct request_queue {TYPE_2__ limits; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_4__ {struct request_queue* queue; } ;

/* Variables and functions */
 scalar_t__ BLK_ZONED_HA ; 
 scalar_t__ BLK_ZONED_HM ; 
 scalar_t__ BLK_ZONED_NONE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  QUEUE_FLAG_ADD_RANDOM ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 scalar_t__ TYPE_ZBC ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 scalar_t__ blk_queue_is_zoned (struct request_queue*) ; 
 int get_unaligned_be16 (unsigned char*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int const,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_get_vpd_page (TYPE_3__*,int,unsigned char*,int const) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*,char*) ; 

__attribute__((used)) static void sd_read_block_characteristics(struct scsi_disk *sdkp)
{
	struct request_queue *q = sdkp->disk->queue;
	unsigned char *buffer;
	u16 rot;
	const int vpd_len = 64;

	buffer = kmalloc(vpd_len, GFP_KERNEL);

	if (!buffer ||
	    /* Block Device Characteristics VPD */
	    scsi_get_vpd_page(sdkp->device, 0xb1, buffer, vpd_len))
		goto out;

	rot = get_unaligned_be16(&buffer[4]);

	if (rot == 1) {
		blk_queue_flag_set(QUEUE_FLAG_NONROT, q);
		blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, q);
	}

	if (sdkp->device->type == TYPE_ZBC) {
		/* Host-managed */
		q->limits.zoned = BLK_ZONED_HM;
	} else {
		sdkp->zoned = (buffer[8] >> 4) & 3;
		if (sdkp->zoned == 1)
			/* Host-aware */
			q->limits.zoned = BLK_ZONED_HA;
		else
			/*
			 * Treat drive-managed devices as
			 * regular block devices.
			 */
			q->limits.zoned = BLK_ZONED_NONE;
	}
	if (blk_queue_is_zoned(q) && sdkp->first_scan)
		sd_printk(KERN_NOTICE, sdkp, "Host-%s zoned block device\n",
		      q->limits.zoned == BLK_ZONED_HM ? "managed" : "aware");

 out:
	kfree(buffer);
}