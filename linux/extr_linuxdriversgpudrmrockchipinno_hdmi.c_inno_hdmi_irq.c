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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct inno_hdmi {TYPE_1__ connector; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  drm_helper_hpd_irq_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t inno_hdmi_irq(int irq, void *dev_id)
{
	struct inno_hdmi *hdmi = dev_id;

	drm_helper_hpd_irq_event(hdmi->connector.dev);

	return IRQ_HANDLED;
}