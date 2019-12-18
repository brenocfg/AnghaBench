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
typedef  scalar_t__ u8 ;
struct dw_hdmi {scalar_t__ i2c; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_IH_MUTE_PHY_STAT0 ; 
 int /*<<< orphan*/  HDMI_IH_PHY_STAT0 ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  dw_hdmi_i2c_irq (struct dw_hdmi*) ; 
 scalar_t__ hdmi_readb (struct dw_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t dw_hdmi_hardirq(int irq, void *dev_id)
{
	struct dw_hdmi *hdmi = dev_id;
	u8 intr_stat;
	irqreturn_t ret = IRQ_NONE;

	if (hdmi->i2c)
		ret = dw_hdmi_i2c_irq(hdmi);

	intr_stat = hdmi_readb(hdmi, HDMI_IH_PHY_STAT0);
	if (intr_stat) {
		hdmi_writeb(hdmi, ~0, HDMI_IH_MUTE_PHY_STAT0);
		return IRQ_WAKE_THREAD;
	}

	return ret;
}