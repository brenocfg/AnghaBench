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
struct lima_sched_pipe {int error; } ;
struct lima_ip {struct lima_device* dev; } ;
struct lima_device {int /*<<< orphan*/  dev; struct lima_sched_pipe* pipe; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  LIMA_GP_INT_CLEAR ; 
 int /*<<< orphan*/  LIMA_GP_INT_MASK ; 
 int /*<<< orphan*/  LIMA_GP_INT_STAT ; 
 int LIMA_GP_IRQ_MASK_ERROR ; 
 int LIMA_GP_IRQ_PLBU_END_CMD_LST ; 
 int LIMA_GP_IRQ_VS_END_CMD_LST ; 
 int /*<<< orphan*/  LIMA_GP_STATUS ; 
 int LIMA_GP_STATUS_PLBU_ACTIVE ; 
 int LIMA_GP_STATUS_VS_ACTIVE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int gp_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gp_write (int /*<<< orphan*/ ,int) ; 
 int lima_pipe_gp ; 
 int /*<<< orphan*/  lima_sched_pipe_task_done (struct lima_sched_pipe*) ; 

__attribute__((used)) static irqreturn_t lima_gp_irq_handler(int irq, void *data)
{
	struct lima_ip *ip = data;
	struct lima_device *dev = ip->dev;
	struct lima_sched_pipe *pipe = dev->pipe + lima_pipe_gp;
	u32 state = gp_read(LIMA_GP_INT_STAT);
	u32 status = gp_read(LIMA_GP_STATUS);
	bool done = false;

	/* for shared irq case */
	if (!state)
		return IRQ_NONE;

	if (state & LIMA_GP_IRQ_MASK_ERROR) {
		dev_err(dev->dev, "gp error irq state=%x status=%x\n",
			state, status);

		/* mask all interrupts before hard reset */
		gp_write(LIMA_GP_INT_MASK, 0);

		pipe->error = true;
		done = true;
	} else {
		bool valid = state & (LIMA_GP_IRQ_VS_END_CMD_LST |
				      LIMA_GP_IRQ_PLBU_END_CMD_LST);
		bool active = status & (LIMA_GP_STATUS_VS_ACTIVE |
					LIMA_GP_STATUS_PLBU_ACTIVE);
		done = valid && !active;
	}

	gp_write(LIMA_GP_INT_CLEAR, state);

	if (done)
		lima_sched_pipe_task_done(pipe);

	return IRQ_HANDLED;
}