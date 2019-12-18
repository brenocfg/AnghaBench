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
struct sti_hdmi {int irq_status; int hpd; int event_received; int /*<<< orphan*/  wait_event; scalar_t__ drm_dev; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int HDMI_INT_AUDIO_FIFO_XRUN ; 
 int HDMI_INT_DLL_LCK ; 
 int HDMI_INT_HOT_PLUG ; 
 int HDMI_INT_SW_RST ; 
 scalar_t__ HDMI_STA ; 
 int HDMI_STA_HOT_PLUG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  drm_helper_hpd_irq_event (scalar_t__) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t hdmi_irq_thread(int irq, void *arg)
{
	struct sti_hdmi *hdmi = arg;

	/* Hot plug/unplug IRQ */
	if (hdmi->irq_status & HDMI_INT_HOT_PLUG) {
		hdmi->hpd = readl(hdmi->regs + HDMI_STA) & HDMI_STA_HOT_PLUG;
		if (hdmi->drm_dev)
			drm_helper_hpd_irq_event(hdmi->drm_dev);
	}

	/* Sw reset and PLL lock are exclusive so we can use the same
	 * event to signal them
	 */
	if (hdmi->irq_status & (HDMI_INT_SW_RST | HDMI_INT_DLL_LCK)) {
		hdmi->event_received = true;
		wake_up_interruptible(&hdmi->wait_event);
	}

	/* Audio FIFO underrun IRQ */
	if (hdmi->irq_status & HDMI_INT_AUDIO_FIFO_XRUN)
		DRM_INFO("Warning: audio FIFO underrun occurs!\n");

	return IRQ_HANDLED;
}