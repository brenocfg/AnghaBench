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
struct dw_hdmi_i2c {unsigned int stat; int /*<<< orphan*/  cmp; } ;
struct dw_hdmi {struct dw_hdmi_i2c* i2c; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_IH_I2CM_STAT0 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 unsigned int hdmi_readb (struct dw_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t dw_hdmi_i2c_irq(struct dw_hdmi *hdmi)
{
	struct dw_hdmi_i2c *i2c = hdmi->i2c;
	unsigned int stat;

	stat = hdmi_readb(hdmi, HDMI_IH_I2CM_STAT0);
	if (!stat)
		return IRQ_NONE;

	hdmi_writeb(hdmi, stat, HDMI_IH_I2CM_STAT0);

	i2c->stat = stat;

	complete(&i2c->cmp);

	return IRQ_HANDLED;
}