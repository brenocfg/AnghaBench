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
typedef  int /*<<< orphan*/  u32 ;
struct xive_irq_data {unsigned long eoi_page; unsigned long esb_shift; unsigned long trig_page; void* trig_mmio; void* eoi_mmio; int /*<<< orphan*/  hw_irq; int /*<<< orphan*/  src_chip; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  XIVE_INVALID_CHIP_ID ; 
 int /*<<< orphan*/  XIVE_IRQ_FLAG_H_INT_ESB ; 
 int /*<<< orphan*/  XIVE_IRQ_FLAG_LSI ; 
 int /*<<< orphan*/  XIVE_IRQ_FLAG_STORE_EOI ; 
 unsigned long XIVE_SRC_H_INT_ESB ; 
 unsigned long XIVE_SRC_LSI ; 
 unsigned long XIVE_SRC_STORE_EOI ; 
 unsigned long XIVE_SRC_TRIGGER ; 
 void* ioremap (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  memset (struct xive_irq_data*,int /*<<< orphan*/ ,int) ; 
 long plpar_int_get_source_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,unsigned long*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xive_spapr_populate_irq_data(u32 hw_irq, struct xive_irq_data *data)
{
	long rc;
	unsigned long flags;
	unsigned long eoi_page;
	unsigned long trig_page;
	unsigned long esb_shift;

	memset(data, 0, sizeof(*data));

	rc = plpar_int_get_source_info(0, hw_irq, &flags, &eoi_page, &trig_page,
				       &esb_shift);
	if (rc)
		return  -EINVAL;

	if (flags & XIVE_SRC_H_INT_ESB)
		data->flags  |= XIVE_IRQ_FLAG_H_INT_ESB;
	if (flags & XIVE_SRC_STORE_EOI)
		data->flags  |= XIVE_IRQ_FLAG_STORE_EOI;
	if (flags & XIVE_SRC_LSI)
		data->flags  |= XIVE_IRQ_FLAG_LSI;
	data->eoi_page  = eoi_page;
	data->esb_shift = esb_shift;
	data->trig_page = trig_page;

	/*
	 * No chip-id for the sPAPR backend. This has an impact how we
	 * pick a target. See xive_pick_irq_target().
	 */
	data->src_chip = XIVE_INVALID_CHIP_ID;

	data->eoi_mmio = ioremap(data->eoi_page, 1u << data->esb_shift);
	if (!data->eoi_mmio) {
		pr_err("Failed to map EOI page for irq 0x%x\n", hw_irq);
		return -ENOMEM;
	}

	data->hw_irq = hw_irq;

	/* Full function page supports trigger */
	if (flags & XIVE_SRC_TRIGGER) {
		data->trig_mmio = data->eoi_mmio;
		return 0;
	}

	data->trig_mmio = ioremap(data->trig_page, 1u << data->esb_shift);
	if (!data->trig_mmio) {
		pr_err("Failed to map trigger page for irq 0x%x\n", hw_irq);
		return -ENOMEM;
	}
	return 0;
}