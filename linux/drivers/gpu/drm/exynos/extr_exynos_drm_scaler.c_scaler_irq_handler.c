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
struct scaler_context {int /*<<< orphan*/  dev; struct exynos_drm_ipp_task* task; } ;
struct exynos_drm_ipp_task {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  exynos_drm_ipp_task_done (struct exynos_drm_ipp_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scaler_disable_int (struct scaler_context*) ; 
 int /*<<< orphan*/  scaler_get_int_status (struct scaler_context*) ; 
 int /*<<< orphan*/  scaler_task_done (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t scaler_irq_handler(int irq, void *arg)
{
	struct scaler_context *scaler = arg;

	u32 val = scaler_get_int_status(scaler);

	scaler_disable_int(scaler);

	if (scaler->task) {
		struct exynos_drm_ipp_task *task = scaler->task;

		scaler->task = NULL;
		pm_runtime_mark_last_busy(scaler->dev);
		pm_runtime_put_autosuspend(scaler->dev);
		exynos_drm_ipp_task_done(task, scaler_task_done(val));
	}

	return IRQ_HANDLED;
}