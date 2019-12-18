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
struct lima_sched_task {struct drm_lima_m450_pp_frame* frame; } ;
struct lima_sched_pipe {struct lima_ip** processor; int /*<<< orphan*/  task; scalar_t__ done; struct lima_ip* bcast_processor; } ;
struct lima_ip {struct lima_device* dev; } ;
struct lima_device {scalar_t__ ip; } ;
struct drm_lima_m450_pp_frame {int num_pp; int /*<<< orphan*/  wb; int /*<<< orphan*/ * frame; int /*<<< orphan*/ * fragment_stack_address; int /*<<< orphan*/ * plbu_array_address; scalar_t__ use_dlbu; int /*<<< orphan*/  dlbu_regs; } ;
struct drm_lima_m400_pp_frame {int num_pp; int /*<<< orphan*/  wb; int /*<<< orphan*/ * frame; int /*<<< orphan*/ * fragment_stack_address; int /*<<< orphan*/ * plbu_array_address; scalar_t__ use_dlbu; int /*<<< orphan*/  dlbu_regs; } ;

/* Variables and functions */
 int LIMA_PP_CTRL ; 
 int /*<<< orphan*/  LIMA_PP_CTRL_START_RENDERING ; 
 int LIMA_PP_FRAME ; 
 int LIMA_PP_STACK ; 
 int /*<<< orphan*/  LIMA_VA_RESERVE_DLBU ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lima_bcast_enable (struct lima_device*,int) ; 
 int /*<<< orphan*/  lima_dlbu_disable (struct lima_device*) ; 
 int /*<<< orphan*/  lima_dlbu_enable (struct lima_device*,int) ; 
 int /*<<< orphan*/  lima_dlbu_set_reg (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lima_ip_dlbu ; 
 int /*<<< orphan*/  lima_pp_soft_reset_async_wait (struct lima_ip*) ; 
 int /*<<< orphan*/  lima_pp_write_frame (struct lima_ip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lima_pp_task_run(struct lima_sched_pipe *pipe,
			     struct lima_sched_task *task)
{
	if (pipe->bcast_processor) {
		struct drm_lima_m450_pp_frame *frame = task->frame;
		struct lima_device *dev = pipe->bcast_processor->dev;
		struct lima_ip *ip = pipe->bcast_processor;
		int i;

		pipe->done = 0;
		atomic_set(&pipe->task, frame->num_pp);

		if (frame->use_dlbu) {
			lima_dlbu_enable(dev, frame->num_pp);

			frame->frame[LIMA_PP_FRAME >> 2] = LIMA_VA_RESERVE_DLBU;
			lima_dlbu_set_reg(dev->ip + lima_ip_dlbu, frame->dlbu_regs);
		} else
			lima_dlbu_disable(dev);

		lima_bcast_enable(dev, frame->num_pp);

		lima_pp_soft_reset_async_wait(ip);

		lima_pp_write_frame(ip, frame->frame, frame->wb);

		for (i = 0; i < frame->num_pp; i++) {
			struct lima_ip *ip = pipe->processor[i];

			pp_write(LIMA_PP_STACK, frame->fragment_stack_address[i]);
			if (!frame->use_dlbu)
				pp_write(LIMA_PP_FRAME, frame->plbu_array_address[i]);
		}

		pp_write(LIMA_PP_CTRL, LIMA_PP_CTRL_START_RENDERING);
	} else {
		struct drm_lima_m400_pp_frame *frame = task->frame;
		int i;

		atomic_set(&pipe->task, frame->num_pp);

		for (i = 0; i < frame->num_pp; i++) {
			struct lima_ip *ip = pipe->processor[i];

			frame->frame[LIMA_PP_FRAME >> 2] =
				frame->plbu_array_address[i];
			frame->frame[LIMA_PP_STACK >> 2] =
				frame->fragment_stack_address[i];

			lima_pp_soft_reset_async_wait(ip);

			lima_pp_write_frame(ip, frame->frame, frame->wb);

			pp_write(LIMA_PP_CTRL, LIMA_PP_CTRL_START_RENDERING);
		}
	}
}