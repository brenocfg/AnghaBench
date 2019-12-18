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
struct vbox_private {int dummy; } ;
struct drm_device {scalar_t__ dev_private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int HGSMIHOSTFLAGS_CURSOR_CAPABILITIES ; 
 int HGSMIHOSTFLAGS_HOTPLUG ; 
 int HGSMIHOSTFLAGS_IRQ ; 
 int HGSMIHOSTFLAGS_VSYNC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  vbox_clear_irq () ; 
 int vbox_get_flags (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_report_hotplug (struct vbox_private*) ; 

irqreturn_t vbox_irq_handler(int irq, void *arg)
{
	struct drm_device *dev = (struct drm_device *)arg;
	struct vbox_private *vbox = (struct vbox_private *)dev->dev_private;
	u32 host_flags = vbox_get_flags(vbox);

	if (!(host_flags & HGSMIHOSTFLAGS_IRQ))
		return IRQ_NONE;

	/*
	 * Due to a bug in the initial host implementation of hot-plug irqs,
	 * the hot-plug and cursor capability flags were never cleared.
	 * Fortunately we can tell when they would have been set by checking
	 * that the VSYNC flag is not set.
	 */
	if (host_flags &
	    (HGSMIHOSTFLAGS_HOTPLUG | HGSMIHOSTFLAGS_CURSOR_CAPABILITIES) &&
	    !(host_flags & HGSMIHOSTFLAGS_VSYNC))
		vbox_report_hotplug(vbox);

	vbox_clear_irq();

	return IRQ_HANDLED;
}