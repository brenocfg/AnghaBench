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
struct fdp1_job {int dummy; } ;
struct fdp1_dev {int /*<<< orphan*/  device_process_lock; } ;
struct fdp1_ctx {struct fdp1_dev* fdp1; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD1_CTL_CLKCTRL ; 
 int /*<<< orphan*/  FD1_CTL_CLKCTRL_CSTP_N ; 
 int /*<<< orphan*/  FD1_CTL_CMD ; 
 int /*<<< orphan*/  FD1_CTL_CMD_STRCMD ; 
 int /*<<< orphan*/  FD1_CTL_IRQENB ; 
 int /*<<< orphan*/  FD1_CTL_IRQ_MASK ; 
 int /*<<< orphan*/  FD1_CTL_REGEND ; 
 int /*<<< orphan*/  FD1_CTL_REGEND_REGEND ; 
 int /*<<< orphan*/  FD1_CTL_SGCMD ; 
 int /*<<< orphan*/  FD1_CTL_SGCMD_SGEN ; 
 int /*<<< orphan*/  FD1_IPC_LMEM ; 
 int /*<<< orphan*/  FD1_IPC_LMEM_LINEAR ; 
 int /*<<< orphan*/  fdp1_configure_deint_mode (struct fdp1_ctx*,struct fdp1_job*) ; 
 int /*<<< orphan*/  fdp1_configure_rpf (struct fdp1_ctx*,struct fdp1_job*) ; 
 int /*<<< orphan*/  fdp1_configure_wpf (struct fdp1_ctx*,struct fdp1_job*) ; 
 int /*<<< orphan*/  fdp1_set_ipc_dli (struct fdp1_ctx*) ; 
 int /*<<< orphan*/  fdp1_set_ipc_sensor (struct fdp1_ctx*) ; 
 int /*<<< orphan*/  fdp1_write (struct fdp1_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fdp1_job* get_queued_job (struct fdp1_dev*) ; 
 int /*<<< orphan*/  queue_hw_job (struct fdp1_dev*,struct fdp1_job*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fdp1_device_process(struct fdp1_ctx *ctx)

{
	struct fdp1_dev *fdp1 = ctx->fdp1;
	struct fdp1_job *job;
	unsigned long flags;

	spin_lock_irqsave(&fdp1->device_process_lock, flags);

	/* Get a job to process */
	job = get_queued_job(fdp1);
	if (!job) {
		/*
		 * VINT can call us to see if we can queue another job.
		 * If we have no work to do, we simply return.
		 */
		spin_unlock_irqrestore(&fdp1->device_process_lock, flags);
		return 0;
	}

	/* First Frame only? ... */
	fdp1_write(fdp1, FD1_CTL_CLKCTRL_CSTP_N, FD1_CTL_CLKCTRL);

	/* Set the mode, and configuration */
	fdp1_configure_deint_mode(ctx, job);

	/* DLI Static Configuration */
	fdp1_set_ipc_dli(ctx);

	/* Sensor Configuration */
	fdp1_set_ipc_sensor(ctx);

	/* Setup the source picture */
	fdp1_configure_rpf(ctx, job);

	/* Setup the destination picture */
	fdp1_configure_wpf(ctx, job);

	/* Line Memory Pixel Number Register for linear access */
	fdp1_write(fdp1, FD1_IPC_LMEM_LINEAR, FD1_IPC_LMEM);

	/* Enable Interrupts */
	fdp1_write(fdp1, FD1_CTL_IRQ_MASK, FD1_CTL_IRQENB);

	/* Finally, the Immediate Registers */

	/* This job is now in the HW queue */
	queue_hw_job(fdp1, job);

	/* Start the command */
	fdp1_write(fdp1, FD1_CTL_CMD_STRCMD, FD1_CTL_CMD);

	/* Registers will update to HW at next VINT */
	fdp1_write(fdp1, FD1_CTL_REGEND_REGEND, FD1_CTL_REGEND);

	/* Enable VINT Generator */
	fdp1_write(fdp1, FD1_CTL_SGCMD_SGEN, FD1_CTL_SGCMD);

	spin_unlock_irqrestore(&fdp1->device_process_lock, flags);

	return 0;
}