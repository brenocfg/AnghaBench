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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct TYPE_2__ {int Status; int /*<<< orphan*/ * ptr; } ;
struct scsi_cmnd {TYPE_1__ SCp; } ;
struct bfad_tskim_s {int dummy; } ;
typedef  enum bfi_tskim_status { ____Placeholder_bfi_tskim_status } bfi_tskim_status ;

/* Variables and functions */
 int /*<<< orphan*/  IO_DONE_BIT ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void
bfa_cb_tskim_done(void *bfad, struct bfad_tskim_s *dtsk,
		   enum bfi_tskim_status tsk_status)
{
	struct scsi_cmnd *cmnd = (struct scsi_cmnd *)dtsk;
	wait_queue_head_t *wq;

	cmnd->SCp.Status |= tsk_status << 1;
	set_bit(IO_DONE_BIT, (unsigned long *)&cmnd->SCp.Status);
	wq = (wait_queue_head_t *) cmnd->SCp.ptr;
	cmnd->SCp.ptr = NULL;

	if (wq)
		wake_up(wq);
}