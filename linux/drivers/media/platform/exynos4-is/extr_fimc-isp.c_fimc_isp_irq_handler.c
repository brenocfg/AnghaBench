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
struct TYPE_2__ {void** args; } ;
struct fimc_is {int /*<<< orphan*/  irq_queue; TYPE_1__ i2h_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIMC_IS_INT_FRAME_DONE_ISP ; 
 int /*<<< orphan*/  MCUCTL_REG_ISSR (int) ; 
 int /*<<< orphan*/  fimc_is_fw_clear_irq1 (struct fimc_is*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_isp_video_irq_handler (struct fimc_is*) ; 
 void* mcuctl_read (struct fimc_is*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void fimc_isp_irq_handler(struct fimc_is *is)
{
	is->i2h_cmd.args[0] = mcuctl_read(is, MCUCTL_REG_ISSR(20));
	is->i2h_cmd.args[1] = mcuctl_read(is, MCUCTL_REG_ISSR(21));

	fimc_is_fw_clear_irq1(is, FIMC_IS_INT_FRAME_DONE_ISP);
	fimc_isp_video_irq_handler(is);

	wake_up(&is->irq_queue);
}