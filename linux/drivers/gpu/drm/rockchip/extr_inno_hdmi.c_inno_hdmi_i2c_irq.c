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
struct inno_hdmi_i2c {int /*<<< orphan*/  cmp; } ;
struct inno_hdmi {struct inno_hdmi_i2c* i2c; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_INTERRUPT_STATUS1 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int hdmi_readb (struct inno_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_writeb (struct inno_hdmi*,int /*<<< orphan*/ ,int) ; 
 int m_INT_EDID_READY ; 

__attribute__((used)) static irqreturn_t inno_hdmi_i2c_irq(struct inno_hdmi *hdmi)
{
	struct inno_hdmi_i2c *i2c = hdmi->i2c;
	u8 stat;

	stat = hdmi_readb(hdmi, HDMI_INTERRUPT_STATUS1);
	if (!(stat & m_INT_EDID_READY))
		return IRQ_NONE;

	/* Clear HDMI EDID interrupt flag */
	hdmi_writeb(hdmi, HDMI_INTERRUPT_STATUS1, m_INT_EDID_READY);

	complete(&i2c->cmp);

	return IRQ_HANDLED;
}