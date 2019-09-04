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
typedef  int u32 ;
struct arasan_cf_dev {int dma_status; TYPE_3__* host; TYPE_2__* qc; int /*<<< orphan*/  cf_completion; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_5__ {TYPE_1__ tf; } ;

/* Variables and functions */
 int ATA_DMA_ERR ; 
 int ATA_TFLAG_WRITE ; 
 int EAGAIN ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int wait4buf(struct arasan_cf_dev *acdev)
{
	if (!wait_for_completion_timeout(&acdev->cf_completion, TIMEOUT)) {
		u32 rw = acdev->qc->tf.flags & ATA_TFLAG_WRITE;

		dev_err(acdev->host->dev, "%s TimeOut", rw ? "write" : "read");
		return -ETIMEDOUT;
	}

	/* Check if PIO Error interrupt has occurred */
	if (acdev->dma_status & ATA_DMA_ERR)
		return -EAGAIN;

	return 0;
}