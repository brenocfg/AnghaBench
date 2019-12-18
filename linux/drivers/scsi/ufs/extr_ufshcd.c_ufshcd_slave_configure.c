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
struct scsi_device {struct request_queue* request_queue; } ;
struct request_queue {int dummy; } ;

/* Variables and functions */
 scalar_t__ PRDT_DATA_BYTE_COUNT_PAD ; 
 int /*<<< orphan*/  blk_queue_update_dma_pad (struct request_queue*,scalar_t__) ; 

__attribute__((used)) static int ufshcd_slave_configure(struct scsi_device *sdev)
{
	struct request_queue *q = sdev->request_queue;

	blk_queue_update_dma_pad(q, PRDT_DATA_BYTE_COUNT_PAD - 1);
	return 0;
}