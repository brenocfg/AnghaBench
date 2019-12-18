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
struct stm32_dcmi {int misr; scalar_t__ overrun_count; int /*<<< orphan*/  irqlock; TYPE_1__* sd_format; int /*<<< orphan*/  errors_count; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int IT_ERR ; 
 int IT_FRAME ; 
 int IT_OVR ; 
 scalar_t__ OVERRUN_ERROR_THRESHOLD ; 
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 int /*<<< orphan*/  dcmi_process_jpeg (struct stm32_dcmi*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t dcmi_irq_thread(int irq, void *arg)
{
	struct stm32_dcmi *dcmi = arg;

	spin_lock_irq(&dcmi->irqlock);

	if (dcmi->misr & IT_OVR) {
		dcmi->overrun_count++;
		if (dcmi->overrun_count > OVERRUN_ERROR_THRESHOLD)
			dcmi->errors_count++;
	}
	if (dcmi->misr & IT_ERR)
		dcmi->errors_count++;

	if (dcmi->sd_format->fourcc == V4L2_PIX_FMT_JPEG &&
	    dcmi->misr & IT_FRAME) {
		/* JPEG received */
		spin_unlock_irq(&dcmi->irqlock);
		dcmi_process_jpeg(dcmi);
		return IRQ_HANDLED;
	}

	spin_unlock_irq(&dcmi->irqlock);
	return IRQ_HANDLED;
}