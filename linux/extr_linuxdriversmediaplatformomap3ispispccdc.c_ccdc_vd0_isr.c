#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct isp_pipeline {int /*<<< orphan*/  frame_number; } ;
struct TYPE_4__ {scalar_t__ state; } ;
struct TYPE_3__ {int /*<<< orphan*/  entity; } ;
struct isp_ccdc_device {scalar_t__ state; int output; int /*<<< orphan*/  lock; int /*<<< orphan*/  shadow_update; TYPE_2__ lsc; scalar_t__ bt656; TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCDC_EVENT_VD0 ; 
 int /*<<< orphan*/  CCDC_EVENT_VD1 ; 
 int CCDC_OUTPUT_MEMORY ; 
 scalar_t__ ISP_PIPELINE_STREAM_CONTINUOUS ; 
 scalar_t__ LSC_STATE_STOPPED ; 
 int /*<<< orphan*/  __ccdc_enable (struct isp_ccdc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ccdc_lsc_enable (struct isp_ccdc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccdc_apply_controls (struct isp_ccdc_device*) ; 
 int /*<<< orphan*/  ccdc_enable (struct isp_ccdc_device*) ; 
 scalar_t__ ccdc_handle_stopping (struct isp_ccdc_device*,int /*<<< orphan*/ ) ; 
 int ccdc_isr_buffer (struct isp_ccdc_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct isp_pipeline* to_isp_pipeline (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccdc_vd0_isr(struct isp_ccdc_device *ccdc)
{
	unsigned long flags;
	int restart = 0;

	/* In BT.656 mode the CCDC doesn't generate an HS/VS interrupt. We thus
	 * need to increment the frame counter here.
	 */
	if (ccdc->bt656) {
		struct isp_pipeline *pipe =
			to_isp_pipeline(&ccdc->subdev.entity);

		atomic_inc(&pipe->frame_number);
	}

	/* Emulate a VD1 interrupt for BT.656 mode, as we can't stop the CCDC in
	 * the VD1 interrupt handler in that mode without risking a CCDC stall
	 * if a short frame is received.
	 */
	if (ccdc->bt656) {
		spin_lock_irqsave(&ccdc->lock, flags);
		if (ccdc->state == ISP_PIPELINE_STREAM_CONTINUOUS &&
		    ccdc->output & CCDC_OUTPUT_MEMORY) {
			if (ccdc->lsc.state != LSC_STATE_STOPPED)
				__ccdc_lsc_enable(ccdc, 0);
			__ccdc_enable(ccdc, 0);
		}
		ccdc_handle_stopping(ccdc, CCDC_EVENT_VD1);
		spin_unlock_irqrestore(&ccdc->lock, flags);
	}

	if (ccdc->output & CCDC_OUTPUT_MEMORY)
		restart = ccdc_isr_buffer(ccdc);

	spin_lock_irqsave(&ccdc->lock, flags);

	if (ccdc_handle_stopping(ccdc, CCDC_EVENT_VD0)) {
		spin_unlock_irqrestore(&ccdc->lock, flags);
		return;
	}

	if (!ccdc->shadow_update)
		ccdc_apply_controls(ccdc);
	spin_unlock_irqrestore(&ccdc->lock, flags);

	if (restart)
		ccdc_enable(ccdc);
}