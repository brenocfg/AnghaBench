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
typedef  int u8 ;
struct rk3066_hdmi {TYPE_1__* i2c; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int stat; int /*<<< orphan*/  cmpltn; } ;

/* Variables and functions */
 int HDMI_INTR_EDID_MASK ; 
 int HDMI_INTR_HOTPLUG ; 
 int HDMI_INTR_MSENS ; 
 int /*<<< orphan*/  HDMI_INTR_STATUS1 ; 
 int /*<<< orphan*/  HDMI_SYS_CTRL ; 
 scalar_t__ HDMI_SYS_POWER_MODE_A ; 
 int HDMI_SYS_POWER_MODE_B ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int hdmi_readb (struct rk3066_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_writeb (struct rk3066_hdmi*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rk3066_hdmi_get_power_mode (struct rk3066_hdmi*) ; 

__attribute__((used)) static irqreturn_t rk3066_hdmi_hardirq(int irq, void *dev_id)
{
	struct rk3066_hdmi *hdmi = dev_id;
	irqreturn_t ret = IRQ_NONE;
	u8 interrupt;

	if (rk3066_hdmi_get_power_mode(hdmi) == HDMI_SYS_POWER_MODE_A)
		hdmi_writeb(hdmi, HDMI_SYS_CTRL, HDMI_SYS_POWER_MODE_B);

	interrupt = hdmi_readb(hdmi, HDMI_INTR_STATUS1);
	if (interrupt)
		hdmi_writeb(hdmi, HDMI_INTR_STATUS1, interrupt);

	if (interrupt & HDMI_INTR_EDID_MASK) {
		hdmi->i2c->stat = interrupt;
		complete(&hdmi->i2c->cmpltn);
	}

	if (interrupt & (HDMI_INTR_HOTPLUG | HDMI_INTR_MSENS))
		ret = IRQ_WAKE_THREAD;

	return ret;
}