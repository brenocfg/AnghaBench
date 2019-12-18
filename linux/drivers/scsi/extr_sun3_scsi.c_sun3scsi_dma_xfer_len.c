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
struct TYPE_2__ {int this_residual; } ;
struct scsi_cmnd {int /*<<< orphan*/  request; TYPE_1__ SCp; } ;
struct NCR5380_hostdata {int dummy; } ;

/* Variables and functions */
 int DMA_MIN_SIZE ; 
 scalar_t__ blk_rq_is_passthrough (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun3scsi_dma_xfer_len(struct NCR5380_hostdata *hostdata,
                                 struct scsi_cmnd *cmd)
{
	int wanted_len = cmd->SCp.this_residual;

	if (wanted_len < DMA_MIN_SIZE || blk_rq_is_passthrough(cmd->request))
		return 0;

	return wanted_len;
}