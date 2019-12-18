#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct scsi_disk {int max_xfer_blocks; int opt_xfer_blocks; unsigned int max_unmap_blocks; int unmap_granularity; int unmap_alignment; scalar_t__ lbpws10; scalar_t__ lbpws; scalar_t__ lbpu; int /*<<< orphan*/  lbpvpd; int /*<<< orphan*/  lbpme; scalar_t__ max_ws_blocks; TYPE_1__* disk; TYPE_2__* device; } ;
struct TYPE_4__ {unsigned int sector_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SD_LBP_DISABLE ; 
 int /*<<< orphan*/  SD_LBP_UNMAP ; 
 int /*<<< orphan*/  SD_LBP_WS10 ; 
 int /*<<< orphan*/  SD_LBP_WS16 ; 
 int /*<<< orphan*/  blk_queue_io_min (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int get_unaligned_be16 (unsigned char*) ; 
 int get_unaligned_be32 (unsigned char*) ; 
 scalar_t__ get_unaligned_be64 (unsigned char*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int const,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_get_vpd_page (TYPE_2__*,int,unsigned char*,int const) ; 
 int /*<<< orphan*/  sd_config_discard (struct scsi_disk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_read_block_limits(struct scsi_disk *sdkp)
{
	unsigned int sector_sz = sdkp->device->sector_size;
	const int vpd_len = 64;
	unsigned char *buffer = kmalloc(vpd_len, GFP_KERNEL);

	if (!buffer ||
	    /* Block Limits VPD */
	    scsi_get_vpd_page(sdkp->device, 0xb0, buffer, vpd_len))
		goto out;

	blk_queue_io_min(sdkp->disk->queue,
			 get_unaligned_be16(&buffer[6]) * sector_sz);

	sdkp->max_xfer_blocks = get_unaligned_be32(&buffer[8]);
	sdkp->opt_xfer_blocks = get_unaligned_be32(&buffer[12]);

	if (buffer[3] == 0x3c) {
		unsigned int lba_count, desc_count;

		sdkp->max_ws_blocks = (u32)get_unaligned_be64(&buffer[36]);

		if (!sdkp->lbpme)
			goto out;

		lba_count = get_unaligned_be32(&buffer[20]);
		desc_count = get_unaligned_be32(&buffer[24]);

		if (lba_count && desc_count)
			sdkp->max_unmap_blocks = lba_count;

		sdkp->unmap_granularity = get_unaligned_be32(&buffer[28]);

		if (buffer[32] & 0x80)
			sdkp->unmap_alignment =
				get_unaligned_be32(&buffer[32]) & ~(1 << 31);

		if (!sdkp->lbpvpd) { /* LBP VPD page not provided */

			if (sdkp->max_unmap_blocks)
				sd_config_discard(sdkp, SD_LBP_UNMAP);
			else
				sd_config_discard(sdkp, SD_LBP_WS16);

		} else {	/* LBP VPD page tells us what to use */
			if (sdkp->lbpu && sdkp->max_unmap_blocks)
				sd_config_discard(sdkp, SD_LBP_UNMAP);
			else if (sdkp->lbpws)
				sd_config_discard(sdkp, SD_LBP_WS16);
			else if (sdkp->lbpws10)
				sd_config_discard(sdkp, SD_LBP_WS10);
			else
				sd_config_discard(sdkp, SD_LBP_DISABLE);
		}
	}

 out:
	kfree(buffer);
}