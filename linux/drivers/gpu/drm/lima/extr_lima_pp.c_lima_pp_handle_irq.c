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

/* Variables and functions */
 int /*<<< orphan*/  LIMA_PP_INT_CLEAR ; 
 int /*<<< orphan*/  LIMA_PP_INT_MASK ; 
 int LIMA_PP_IRQ_MASK_ERROR ; 
 int /*<<< orphan*/  LIMA_PP_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int lima_pipe_pp ; 
 int pp_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lima_pp_handle_irq(struct lima_ip *ip, u32 state)
{
	struct lima_device *dev = ip->dev;
	struct lima_sched_pipe *pipe = dev->pipe + lima_pipe_pp;

	if (state & LIMA_PP_IRQ_MASK_ERROR) {
		u32 status = pp_read(LIMA_PP_STATUS);

		dev_err(dev->dev, "pp error irq state=%x status=%x\n",
			state, status);

		pipe->error = true;

		/* mask all interrupts before hard reset */
		pp_write(LIMA_PP_INT_MASK, 0);
	}

	pp_write(LIMA_PP_INT_CLEAR, state);
}