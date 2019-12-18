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
struct lima_sched_task {struct drm_lima_gp_frame* frame; } ;
struct lima_sched_pipe {struct lima_ip** processor; } ;
struct lima_ip {scalar_t__ iomem; } ;
struct drm_lima_gp_frame {int /*<<< orphan*/ * frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMA_GP_CMD ; 
 int /*<<< orphan*/  LIMA_GP_CMD_START_PLBU ; 
 int /*<<< orphan*/  LIMA_GP_CMD_START_VS ; 
 int /*<<< orphan*/  LIMA_GP_CMD_UPDATE_PLBU_ALLOC ; 
 int LIMA_GP_FRAME_REG_NUM ; 
 int LIMA_GP_PLBUCL_END_ADDR ; 
 int LIMA_GP_PLBUCL_START_ADDR ; 
 int LIMA_GP_VSCL_END_ADDR ; 
 int LIMA_GP_VSCL_START_ADDR ; 
 int /*<<< orphan*/  gp_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lima_gp_soft_reset_async_wait (struct lima_ip*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void lima_gp_task_run(struct lima_sched_pipe *pipe,
			     struct lima_sched_task *task)
{
	struct lima_ip *ip = pipe->processor[0];
	struct drm_lima_gp_frame *frame = task->frame;
	u32 *f = frame->frame;
	u32 cmd = 0;
	int i;

	if (f[LIMA_GP_VSCL_START_ADDR >> 2] !=
	    f[LIMA_GP_VSCL_END_ADDR >> 2])
		cmd |= LIMA_GP_CMD_START_VS;
	if (f[LIMA_GP_PLBUCL_START_ADDR >> 2] !=
	    f[LIMA_GP_PLBUCL_END_ADDR >> 2])
		cmd |= LIMA_GP_CMD_START_PLBU;

	/* before any hw ops, wait last success task async soft reset */
	lima_gp_soft_reset_async_wait(ip);

	for (i = 0; i < LIMA_GP_FRAME_REG_NUM; i++)
		writel(f[i], ip->iomem + LIMA_GP_VSCL_START_ADDR + i * 4);

	gp_write(LIMA_GP_CMD, LIMA_GP_CMD_UPDATE_PLBU_ALLOC);
	gp_write(LIMA_GP_CMD, cmd);
}