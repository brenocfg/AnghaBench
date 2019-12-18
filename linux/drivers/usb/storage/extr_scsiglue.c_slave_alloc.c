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
struct us_data {scalar_t__ protocol; scalar_t__ max_lun; } ;
struct scsi_device {int inquiry_len; int /*<<< orphan*/  sdev_bflags; int /*<<< orphan*/  request_queue; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLIST_FORCELUN ; 
 scalar_t__ USB_PR_BULK ; 
 int /*<<< orphan*/  blk_queue_update_dma_alignment (int /*<<< orphan*/ ,int) ; 
 struct us_data* host_to_us (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int slave_alloc (struct scsi_device *sdev)
{
	struct us_data *us = host_to_us(sdev->host);

	/*
	 * Set the INQUIRY transfer length to 36.  We don't use any of
	 * the extra data and many devices choke if asked for more or
	 * less than 36 bytes.
	 */
	sdev->inquiry_len = 36;

	/*
	 * Some host controllers may have alignment requirements.
	 * We'll play it safe by requiring 512-byte alignment always.
	 */
	blk_queue_update_dma_alignment(sdev->request_queue, (512 - 1));

	/* Tell the SCSI layer if we know there is more than one LUN */
	if (us->protocol == USB_PR_BULK && us->max_lun > 0)
		sdev->sdev_bflags |= BLIST_FORCELUN;

	return 0;
}