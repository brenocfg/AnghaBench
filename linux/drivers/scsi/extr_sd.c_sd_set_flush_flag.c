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
struct scsi_disk {TYPE_1__* disk; scalar_t__ DPOFUA; scalar_t__ WCE; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_queue_write_cache (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void sd_set_flush_flag(struct scsi_disk *sdkp)
{
	bool wc = false, fua = false;

	if (sdkp->WCE) {
		wc = true;
		if (sdkp->DPOFUA)
			fua = true;
	}

	blk_queue_write_cache(sdkp->disk->queue, wc, fua);
}