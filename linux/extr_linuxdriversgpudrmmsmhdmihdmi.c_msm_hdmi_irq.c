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
struct hdmi {scalar_t__ hdcp_ctrl; int /*<<< orphan*/  i2c; int /*<<< orphan*/  connector; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  msm_hdmi_connector_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_hdmi_hdcp_irq (scalar_t__) ; 
 int /*<<< orphan*/  msm_hdmi_i2c_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t msm_hdmi_irq(int irq, void *dev_id)
{
	struct hdmi *hdmi = dev_id;

	/* Process HPD: */
	msm_hdmi_connector_irq(hdmi->connector);

	/* Process DDC: */
	msm_hdmi_i2c_irq(hdmi->i2c);

	/* Process HDCP: */
	if (hdmi->hdcp_ctrl)
		msm_hdmi_hdcp_irq(hdmi->hdcp_ctrl);

	/* TODO audio.. */

	return IRQ_HANDLED;
}