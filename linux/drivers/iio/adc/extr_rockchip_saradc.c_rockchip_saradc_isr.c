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
struct rockchip_saradc {int /*<<< orphan*/  completion; scalar_t__ regs; TYPE_1__* data; int /*<<< orphan*/  last_val; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ num_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ SARADC_CTRL ; 
 scalar_t__ SARADC_DATA ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t rockchip_saradc_isr(int irq, void *dev_id)
{
	struct rockchip_saradc *info = dev_id;

	/* Read value */
	info->last_val = readl_relaxed(info->regs + SARADC_DATA);
	info->last_val &= GENMASK(info->data->num_bits - 1, 0);

	/* Clear irq & power down adc */
	writel_relaxed(0, info->regs + SARADC_CTRL);

	complete(&info->completion);

	return IRQ_HANDLED;
}