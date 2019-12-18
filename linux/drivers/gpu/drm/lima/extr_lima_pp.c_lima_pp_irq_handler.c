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
typedef  int /*<<< orphan*/  u32 ;
struct lima_sched_pipe {int /*<<< orphan*/  task; } ;
struct lima_ip {struct lima_device* dev; } ;
struct lima_device {struct lima_sched_pipe* pipe; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  LIMA_PP_INT_STATUS ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int lima_pipe_pp ; 
 int /*<<< orphan*/  lima_pp_handle_irq (struct lima_ip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lima_sched_pipe_task_done (struct lima_sched_pipe*) ; 
 int /*<<< orphan*/  pp_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t lima_pp_irq_handler(int irq, void *data)
{
	struct lima_ip *ip = data;
	struct lima_device *dev = ip->dev;
	struct lima_sched_pipe *pipe = dev->pipe + lima_pipe_pp;
	u32 state = pp_read(LIMA_PP_INT_STATUS);

	/* for shared irq case */
	if (!state)
		return IRQ_NONE;

	lima_pp_handle_irq(ip, state);

	if (atomic_dec_and_test(&pipe->task))
		lima_sched_pipe_task_done(pipe);

	return IRQ_HANDLED;
}