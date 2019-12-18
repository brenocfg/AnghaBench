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
struct scsi_device {int /*<<< orphan*/  request_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_queue_dma_alignment (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mts_slave_configure (struct scsi_device *s)
{
	blk_queue_dma_alignment(s->request_queue, (512 - 1));
	return 0;
}