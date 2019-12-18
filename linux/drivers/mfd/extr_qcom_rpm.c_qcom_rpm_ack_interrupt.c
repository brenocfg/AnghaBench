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
typedef  int u32 ;
struct qcom_rpm {int ack_status; int /*<<< orphan*/  ack; int /*<<< orphan*/  dev; TYPE_1__* data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int ack_sel_size; scalar_t__ ack_ctx_off; scalar_t__ ack_sel_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RPM_CTRL_REG (struct qcom_rpm*,scalar_t__) ; 
 int RPM_NOTIFICATION ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t qcom_rpm_ack_interrupt(int irq, void *dev)
{
	struct qcom_rpm *rpm = dev;
	u32 ack;
	int i;

	ack = readl_relaxed(RPM_CTRL_REG(rpm, rpm->data->ack_ctx_off));
	for (i = 0; i < rpm->data->ack_sel_size; i++)
		writel_relaxed(0,
			RPM_CTRL_REG(rpm, rpm->data->ack_sel_off + i));
	writel(0, RPM_CTRL_REG(rpm, rpm->data->ack_ctx_off));

	if (ack & RPM_NOTIFICATION) {
		dev_warn(rpm->dev, "ignoring notification!\n");
	} else {
		rpm->ack_status = ack;
		complete(&rpm->ack);
	}

	return IRQ_HANDLED;
}