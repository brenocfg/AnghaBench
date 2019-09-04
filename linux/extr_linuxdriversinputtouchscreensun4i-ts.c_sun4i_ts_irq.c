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
typedef  int u32 ;
struct sun4i_ts_data {scalar_t__ base; scalar_t__ input; void* temp_data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TEMP_DATA ; 
 int TEMP_DATA_PENDING ; 
 scalar_t__ TP_INT_FIFOS ; 
 void* readl (scalar_t__) ; 
 int /*<<< orphan*/  sun4i_ts_irq_handle_input (struct sun4i_ts_data*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t sun4i_ts_irq(int irq, void *dev_id)
{
	struct sun4i_ts_data *ts = dev_id;
	u32 reg_val;

	reg_val  = readl(ts->base + TP_INT_FIFOS);

	if (reg_val & TEMP_DATA_PENDING)
		ts->temp_data = readl(ts->base + TEMP_DATA);

	if (ts->input)
		sun4i_ts_irq_handle_input(ts, reg_val);

	writel(reg_val, ts->base + TP_INT_FIFOS);

	return IRQ_HANDLED;
}