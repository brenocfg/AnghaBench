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
struct dsi_reg {int dummy; } ;
struct dsi_isr_data {int mask; int /*<<< orphan*/ * isr; } ;
struct dsi_data {int dummy; } ;

/* Variables and functions */
 int dsi_read_reg (struct dsi_data*,struct dsi_reg const) ; 
 int /*<<< orphan*/  dsi_write_reg (struct dsi_data*,struct dsi_reg const,int) ; 

__attribute__((used)) static void _omap_dsi_configure_irqs(struct dsi_data *dsi,
				     struct dsi_isr_data *isr_array,
				     unsigned int isr_array_size,
				     u32 default_mask,
				     const struct dsi_reg enable_reg,
				     const struct dsi_reg status_reg)
{
	struct dsi_isr_data *isr_data;
	u32 mask;
	u32 old_mask;
	int i;

	mask = default_mask;

	for (i = 0; i < isr_array_size; i++) {
		isr_data = &isr_array[i];

		if (isr_data->isr == NULL)
			continue;

		mask |= isr_data->mask;
	}

	old_mask = dsi_read_reg(dsi, enable_reg);
	/* clear the irqstatus for newly enabled irqs */
	dsi_write_reg(dsi, status_reg, (mask ^ old_mask) & mask);
	dsi_write_reg(dsi, enable_reg, mask);

	/* flush posted writes */
	dsi_read_reg(dsi, enable_reg);
	dsi_read_reg(dsi, status_reg);
}