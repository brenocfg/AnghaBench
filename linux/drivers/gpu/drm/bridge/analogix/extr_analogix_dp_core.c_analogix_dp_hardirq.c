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
struct analogix_dp_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum dp_irq_type { ____Placeholder_dp_irq_type } dp_irq_type ;

/* Variables and functions */
 int DP_IRQ_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int analogix_dp_get_irq_type (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  analogix_dp_mute_hpd_interrupt (struct analogix_dp_device*) ; 

__attribute__((used)) static irqreturn_t analogix_dp_hardirq(int irq, void *arg)
{
	struct analogix_dp_device *dp = arg;
	irqreturn_t ret = IRQ_NONE;
	enum dp_irq_type irq_type;

	irq_type = analogix_dp_get_irq_type(dp);
	if (irq_type != DP_IRQ_TYPE_UNKNOWN) {
		analogix_dp_mute_hpd_interrupt(dp);
		ret = IRQ_WAKE_THREAD;
	}

	return ret;
}