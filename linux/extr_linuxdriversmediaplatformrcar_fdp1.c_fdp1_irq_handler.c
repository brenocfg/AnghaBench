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
typedef  int u32 ;
struct fdp1_dev {int clk_rate; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  int_status ;

/* Variables and functions */
 int /*<<< orphan*/  FD1_CTL_IRQSTA ; 
 int FD1_CTL_IRQ_FREE ; 
 int FD1_CTL_IRQ_MASK ; 
 int FD1_CTL_IRQ_VERE ; 
 int FD1_CTL_IRQ_VINTE ; 
 int /*<<< orphan*/  FD1_CTL_STATUS ; 
 int FD1_CTL_STATUS_BSY ; 
 int FD1_CTL_STATUS_SGFREND ; 
 int FD1_CTL_STATUS_SGREGSET ; 
 int FD1_CTL_STATUS_SGVERR ; 
 int FD1_CTL_STATUS_VINT_CNT_MASK ; 
 int FD1_CTL_STATUS_VINT_CNT_SHIFT ; 
 int /*<<< orphan*/  FD1_CTL_VCYCLE_STAT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int debug ; 
 int /*<<< orphan*/  device_frame_end (struct fdp1_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (struct fdp1_dev*,char*,...) ; 
 int fdp1_read (struct fdp1_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdp1_write (struct fdp1_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t fdp1_irq_handler(int irq, void *dev_id)
{
	struct fdp1_dev *fdp1 = dev_id;
	u32 int_status;
	u32 ctl_status;
	u32 vint_cnt;
	u32 cycles;

	int_status = fdp1_read(fdp1, FD1_CTL_IRQSTA);
	cycles = fdp1_read(fdp1, FD1_CTL_VCYCLE_STAT);
	ctl_status = fdp1_read(fdp1, FD1_CTL_STATUS);
	vint_cnt = (ctl_status & FD1_CTL_STATUS_VINT_CNT_MASK) >>
			FD1_CTL_STATUS_VINT_CNT_SHIFT;

	/* Clear interrupts */
	fdp1_write(fdp1, ~(int_status) & FD1_CTL_IRQ_MASK, FD1_CTL_IRQSTA);

	if (debug >= 2) {
		dprintk(fdp1, "IRQ: 0x%x %s%s%s\n", int_status,
			int_status & FD1_CTL_IRQ_VERE ? "[Error]" : "[!E]",
			int_status & FD1_CTL_IRQ_VINTE ? "[VSync]" : "[!V]",
			int_status & FD1_CTL_IRQ_FREE ? "[FrameEnd]" : "[!F]");

		dprintk(fdp1, "CycleStatus = %d (%dms)\n",
			cycles, cycles/(fdp1->clk_rate/1000));

		dprintk(fdp1,
			"Control Status = 0x%08x : VINT_CNT = %d %s:%s:%s:%s\n",
			ctl_status, vint_cnt,
			ctl_status & FD1_CTL_STATUS_SGREGSET ? "RegSet" : "",
			ctl_status & FD1_CTL_STATUS_SGVERR ? "Vsync Error" : "",
			ctl_status & FD1_CTL_STATUS_SGFREND ? "FrameEnd" : "",
			ctl_status & FD1_CTL_STATUS_BSY ? "Busy" : "");
		dprintk(fdp1, "***********************************\n");
	}

	/* Spurious interrupt */
	if (!(FD1_CTL_IRQ_MASK & int_status))
		return IRQ_NONE;

	/* Work completed, release the frame */
	if (FD1_CTL_IRQ_VERE & int_status)
		device_frame_end(fdp1, VB2_BUF_STATE_ERROR);
	else if (FD1_CTL_IRQ_FREE & int_status)
		device_frame_end(fdp1, VB2_BUF_STATE_DONE);

	return IRQ_HANDLED;
}