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
struct analogix_dp_device {scalar_t__ drm_dev; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum dp_irq_type { ____Placeholder_dp_irq_type } dp_irq_type ;

/* Variables and functions */
 int DP_IRQ_TYPE_HP_CABLE_IN ; 
 int DP_IRQ_TYPE_HP_CABLE_OUT ; 
 int DP_IRQ_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  analogix_dp_clear_hotplug_interrupts (struct analogix_dp_device*) ; 
 int analogix_dp_get_irq_type (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  analogix_dp_unmute_hpd_interrupt (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drm_helper_hpd_irq_event (scalar_t__) ; 

__attribute__((used)) static irqreturn_t analogix_dp_irq_thread(int irq, void *arg)
{
	struct analogix_dp_device *dp = arg;
	enum dp_irq_type irq_type;

	irq_type = analogix_dp_get_irq_type(dp);
	if (irq_type & DP_IRQ_TYPE_HP_CABLE_IN ||
	    irq_type & DP_IRQ_TYPE_HP_CABLE_OUT) {
		dev_dbg(dp->dev, "Detected cable status changed!\n");
		if (dp->drm_dev)
			drm_helper_hpd_irq_event(dp->drm_dev);
	}

	if (irq_type != DP_IRQ_TYPE_UNKNOWN) {
		analogix_dp_clear_hotplug_interrupts(dp);
		analogix_dp_unmute_hpd_interrupt(dp);
	}

	return IRQ_HANDLED;
}