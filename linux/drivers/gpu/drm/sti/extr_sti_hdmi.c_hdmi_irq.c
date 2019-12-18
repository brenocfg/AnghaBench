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
struct sti_hdmi {int /*<<< orphan*/  irq_status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_INT_CLR ; 
 int /*<<< orphan*/  HDMI_INT_STA ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  hdmi_read (struct sti_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write (struct sti_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t hdmi_irq(int irq, void *arg)
{
	struct sti_hdmi *hdmi = arg;

	/* read interrupt status */
	hdmi->irq_status = hdmi_read(hdmi, HDMI_INT_STA);

	/* clear interrupt status */
	hdmi_write(hdmi, hdmi->irq_status, HDMI_INT_CLR);

	/* force sync bus write */
	hdmi_read(hdmi, HDMI_INT_STA);

	return IRQ_WAKE_THREAD;
}