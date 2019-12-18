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
typedef  int u8 ;
struct inno_hdmi {scalar_t__ i2c; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_STATUS ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  hdmi_modb (struct inno_hdmi*,int /*<<< orphan*/ ,int,int) ; 
 int hdmi_readb (struct inno_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inno_hdmi_i2c_irq (struct inno_hdmi*) ; 
 int m_INT_HOTPLUG ; 

__attribute__((used)) static irqreturn_t inno_hdmi_hardirq(int irq, void *dev_id)
{
	struct inno_hdmi *hdmi = dev_id;
	irqreturn_t ret = IRQ_NONE;
	u8 interrupt;

	if (hdmi->i2c)
		ret = inno_hdmi_i2c_irq(hdmi);

	interrupt = hdmi_readb(hdmi, HDMI_STATUS);
	if (interrupt & m_INT_HOTPLUG) {
		hdmi_modb(hdmi, HDMI_STATUS, m_INT_HOTPLUG, m_INT_HOTPLUG);
		ret = IRQ_WAKE_THREAD;
	}

	return ret;
}