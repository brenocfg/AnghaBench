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
struct wm8350_platform_data {int irq_base; scalar_t__ irq_high; } ;
struct wm8350 {int chip_irq; int irq_base; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/ * irq_masks; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_HIGH ; 
 int IRQF_TRIGGER_LOW ; 
 int IRQ_NOPROBE ; 
 int IRQ_NOREQUEST ; 
 scalar_t__ WM8350_INT_STATUS_1_MASK ; 
 int /*<<< orphan*/  WM8350_IRQ_POL ; 
 int /*<<< orphan*/  WM8350_SYSTEM_CONTROL_1 ; 
 scalar_t__ WM8350_SYSTEM_INTERRUPTS_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int irq_alloc_descs (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_clear_status_flags (int,int) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (int,struct wm8350*) ; 
 int /*<<< orphan*/  irq_set_nested_thread (int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct wm8350*) ; 
 int /*<<< orphan*/  wm8350_clear_bits (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_irq ; 
 int /*<<< orphan*/  wm8350_irq_chip ; 
 int /*<<< orphan*/ * wm8350_irqs ; 
 int /*<<< orphan*/  wm8350_reg_read (struct wm8350*,scalar_t__) ; 
 int /*<<< orphan*/  wm8350_reg_write (struct wm8350*,scalar_t__,int) ; 
 int /*<<< orphan*/  wm8350_set_bits (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wm8350_irq_init(struct wm8350 *wm8350, int irq,
		    struct wm8350_platform_data *pdata)
{
	int ret, cur_irq, i;
	int flags = IRQF_ONESHOT;
	int irq_base = -1;

	if (!irq) {
		dev_warn(wm8350->dev, "No interrupt support, no core IRQ\n");
		return 0;
	}

	/* Mask top level interrupts */
	wm8350_reg_write(wm8350, WM8350_SYSTEM_INTERRUPTS_MASK, 0xFFFF);

	/* Mask all individual interrupts by default and cache the
	 * masks.  We read the masks back since there are unwritable
	 * bits in the mask registers. */
	for (i = 0; i < ARRAY_SIZE(wm8350->irq_masks); i++) {
		wm8350_reg_write(wm8350, WM8350_INT_STATUS_1_MASK + i,
				 0xFFFF);
		wm8350->irq_masks[i] =
			wm8350_reg_read(wm8350,
					WM8350_INT_STATUS_1_MASK + i);
	}

	mutex_init(&wm8350->irq_lock);
	wm8350->chip_irq = irq;

	if (pdata && pdata->irq_base > 0)
		irq_base = pdata->irq_base;

	wm8350->irq_base =
		irq_alloc_descs(irq_base, 0, ARRAY_SIZE(wm8350_irqs), 0);
	if (wm8350->irq_base < 0) {
		dev_warn(wm8350->dev, "Allocating irqs failed with %d\n",
			wm8350->irq_base);
		return 0;
	}

	if (pdata && pdata->irq_high) {
		flags |= IRQF_TRIGGER_HIGH;

		wm8350_set_bits(wm8350, WM8350_SYSTEM_CONTROL_1,
				WM8350_IRQ_POL);
	} else {
		flags |= IRQF_TRIGGER_LOW;

		wm8350_clear_bits(wm8350, WM8350_SYSTEM_CONTROL_1,
				  WM8350_IRQ_POL);
	}

	/* Register with genirq */
	for (cur_irq = wm8350->irq_base;
	     cur_irq < ARRAY_SIZE(wm8350_irqs) + wm8350->irq_base;
	     cur_irq++) {
		irq_set_chip_data(cur_irq, wm8350);
		irq_set_chip_and_handler(cur_irq, &wm8350_irq_chip,
					 handle_edge_irq);
		irq_set_nested_thread(cur_irq, 1);

		irq_clear_status_flags(cur_irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	}

	ret = request_threaded_irq(irq, NULL, wm8350_irq, flags,
				   "wm8350", wm8350);
	if (ret != 0)
		dev_err(wm8350->dev, "Failed to request IRQ: %d\n", ret);

	/* Allow interrupts to fire */
	wm8350_reg_write(wm8350, WM8350_SYSTEM_INTERRUPTS_MASK, 0);

	return ret;
}