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
struct TYPE_2__ {int flag; } ;
struct fmdev {int /*<<< orphan*/  maintask_comp; TYPE_1__ irq_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_LOW_RSSI_START_IDX ; 
 int FM_POW_ENB_EVENT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fm_irq_call_stage (struct fmdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmdbg (char*) ; 

__attribute__((used)) static void fm_irq_handle_power_enb(struct fmdev *fmdev)
{
	if (fmdev->irq_info.flag & FM_POW_ENB_EVENT) {
		fmdbg("irq: Power Enabled/Disabled\n");
		complete(&fmdev->maintask_comp);
	}

	fm_irq_call_stage(fmdev, FM_LOW_RSSI_START_IDX);
}