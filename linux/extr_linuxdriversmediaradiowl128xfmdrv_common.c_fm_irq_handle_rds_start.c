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
struct TYPE_2__ {int flag; int mask; int /*<<< orphan*/  stage; } ;
struct fmdev {TYPE_1__ irq_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_HW_TUNE_OP_ENDED_IDX ; 
 int FM_RDS_EVENT ; 
 int /*<<< orphan*/  FM_RDS_SEND_RDS_GETCMD_IDX ; 
 int /*<<< orphan*/  fm_irq_call (struct fmdev*) ; 
 int /*<<< orphan*/  fmdbg (char*) ; 

__attribute__((used)) static void fm_irq_handle_rds_start(struct fmdev *fmdev)
{
	if (fmdev->irq_info.flag & FM_RDS_EVENT & fmdev->irq_info.mask) {
		fmdbg("irq: rds threshold reached\n");
		fmdev->irq_info.stage = FM_RDS_SEND_RDS_GETCMD_IDX;
	} else {
		/* Continue next function in interrupt handler table */
		fmdev->irq_info.stage = FM_HW_TUNE_OP_ENDED_IDX;
	}

	fm_irq_call(fmdev);
}