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
struct TYPE_2__ {int flag; int mask; void* stage; } ;
struct fmdev {TYPE_1__ irq_info; int /*<<< orphan*/  maintask_comp; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 void* FM_AF_JUMP_RD_FREQ_IDX ; 
 int /*<<< orphan*/  FM_AF_SWITCH_INPROGRESS ; 
 int FM_BL_EVENT ; 
 int FM_FR_EVENT ; 
 void* FM_HW_POWER_ENB_IDX ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fm_irq_call (struct fmdev*) ; 
 int /*<<< orphan*/  fmdbg (char*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fm_irq_handle_tune_op_ended(struct fmdev *fmdev)
{
	if (fmdev->irq_info.flag & (FM_FR_EVENT | FM_BL_EVENT) & fmdev->
	    irq_info.mask) {
		fmdbg("irq: tune ended/bandlimit reached\n");
		if (test_and_clear_bit(FM_AF_SWITCH_INPROGRESS, &fmdev->flag)) {
			fmdev->irq_info.stage = FM_AF_JUMP_RD_FREQ_IDX;
		} else {
			complete(&fmdev->maintask_comp);
			fmdev->irq_info.stage = FM_HW_POWER_ENB_IDX;
		}
	} else
		fmdev->irq_info.stage = FM_HW_POWER_ENB_IDX;

	fm_irq_call(fmdev);
}