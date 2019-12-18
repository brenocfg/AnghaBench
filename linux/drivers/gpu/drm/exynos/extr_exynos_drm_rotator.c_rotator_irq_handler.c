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
struct rot_context {int /*<<< orphan*/  dev; struct exynos_drm_ipp_task* task; } ;
struct exynos_drm_ipp_task {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum rot_irq_status { ____Placeholder_rot_irq_status } rot_irq_status ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int ROT_IRQ_STATUS_COMPLETE ; 
 int /*<<< orphan*/  ROT_STATUS ; 
 int /*<<< orphan*/  ROT_STATUS_IRQ_PENDING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_drm_ipp_task_done (struct exynos_drm_ipp_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rot_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rot_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rotator_reg_get_irq_status (struct rot_context*) ; 

__attribute__((used)) static irqreturn_t rotator_irq_handler(int irq, void *arg)
{
	struct rot_context *rot = arg;
	enum rot_irq_status irq_status;
	u32 val;

	/* Get execution result */
	irq_status = rotator_reg_get_irq_status(rot);

	/* clear status */
	val = rot_read(ROT_STATUS);
	val |= ROT_STATUS_IRQ_PENDING((u32)irq_status);
	rot_write(val, ROT_STATUS);

	if (rot->task) {
		struct exynos_drm_ipp_task *task = rot->task;

		rot->task = NULL;
		pm_runtime_mark_last_busy(rot->dev);
		pm_runtime_put_autosuspend(rot->dev);
		exynos_drm_ipp_task_done(task,
			irq_status == ROT_IRQ_STATUS_COMPLETE ? 0 : -EINVAL);
	}

	return IRQ_HANDLED;
}