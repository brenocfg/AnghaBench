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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  active; } ;
struct isp_prev_device {scalar_t__ input; int output; scalar_t__ state; TYPE_1__ params; int /*<<< orphan*/  stopping; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 scalar_t__ ISP_PIPELINE_STREAM_CONTINUOUS ; 
 scalar_t__ PREVIEW_INPUT_MEMORY ; 
 int PREVIEW_OUTPUT_MEMORY ; 
 scalar_t__ omap3isp_module_sync_is_stopping (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preview_config_input_size (struct isp_prev_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preview_enable_oneshot (struct isp_prev_device*) ; 
 int /*<<< orphan*/  preview_isr_buffer (struct isp_prev_device*) ; 
 int /*<<< orphan*/  preview_params_lock (struct isp_prev_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  preview_params_switch (struct isp_prev_device*) ; 
 int /*<<< orphan*/  preview_params_unlock (struct isp_prev_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  preview_setup_hw (struct isp_prev_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void omap3isp_preview_isr(struct isp_prev_device *prev)
{
	unsigned long flags;
	u32 update;
	u32 active;

	if (omap3isp_module_sync_is_stopping(&prev->wait, &prev->stopping))
		return;

	spin_lock_irqsave(&prev->params.lock, flags);
	preview_params_switch(prev);
	update = preview_params_lock(prev, 0, false);
	active = prev->params.active;
	spin_unlock_irqrestore(&prev->params.lock, flags);

	preview_setup_hw(prev, update, active);
	preview_config_input_size(prev, active);

	if (prev->input == PREVIEW_INPUT_MEMORY ||
	    prev->output & PREVIEW_OUTPUT_MEMORY)
		preview_isr_buffer(prev);
	else if (prev->state == ISP_PIPELINE_STREAM_CONTINUOUS)
		preview_enable_oneshot(prev);

	spin_lock_irqsave(&prev->params.lock, flags);
	preview_params_unlock(prev, update, false);
	spin_unlock_irqrestore(&prev->params.lock, flags);
}