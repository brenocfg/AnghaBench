#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wm831x_pdata {scalar_t__ irq_cmos; scalar_t__ irq_base; } ;
struct wm831x {int* irq_masks_cur; int* irq_masks_cache; int irq; TYPE_1__* dev; struct irq_domain* irq_domain; int /*<<< orphan*/  irq_lock; struct wm831x_pdata pdata; } ;
struct irq_domain {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ WM831X_INTERRUPT_STATUS_1_MASK ; 
 int /*<<< orphan*/  WM831X_IRQ_CONFIG ; 
 int WM831X_IRQ_OD ; 
 int /*<<< orphan*/  WM831X_NUM_IRQS ; 
 scalar_t__ WM831X_SYSTEM_INTERRUPTS_MASK ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,...) ; 
 int enable_irq_wake (int) ; 
 int irq_alloc_descs (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct irq_domain* irq_domain_add_legacy (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct wm831x*) ; 
 struct irq_domain* irq_domain_add_linear (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct wm831x*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct wm831x*) ; 
 int /*<<< orphan*/  wm831x_irq_domain_ops ; 
 int /*<<< orphan*/  wm831x_irq_thread ; 
 int* wm831x_irqs ; 
 int /*<<< orphan*/  wm831x_reg_write (struct wm831x*,scalar_t__,int) ; 
 int /*<<< orphan*/  wm831x_set_bits (struct wm831x*,int /*<<< orphan*/ ,int,int) ; 

int wm831x_irq_init(struct wm831x *wm831x, int irq)
{
	struct wm831x_pdata *pdata = &wm831x->pdata;
	struct irq_domain *domain;
	int i, ret, irq_base;

	mutex_init(&wm831x->irq_lock);

	/* Mask the individual interrupt sources */
	for (i = 0; i < ARRAY_SIZE(wm831x->irq_masks_cur); i++) {
		wm831x->irq_masks_cur[i] = 0xffff;
		wm831x->irq_masks_cache[i] = 0xffff;
		wm831x_reg_write(wm831x, WM831X_INTERRUPT_STATUS_1_MASK + i,
				 0xffff);
	}

	/* Try to dynamically allocate IRQs if no base is specified */
	if (pdata->irq_base) {
		irq_base = irq_alloc_descs(pdata->irq_base, 0,
					   WM831X_NUM_IRQS, 0);
		if (irq_base < 0) {
			dev_warn(wm831x->dev, "Failed to allocate IRQs: %d\n",
				 irq_base);
			irq_base = 0;
		}
	} else {
		irq_base = 0;
	}

	if (irq_base)
		domain = irq_domain_add_legacy(wm831x->dev->of_node,
					       ARRAY_SIZE(wm831x_irqs),
					       irq_base, 0,
					       &wm831x_irq_domain_ops,
					       wm831x);
	else
		domain = irq_domain_add_linear(wm831x->dev->of_node,
					       ARRAY_SIZE(wm831x_irqs),
					       &wm831x_irq_domain_ops,
					       wm831x);

	if (!domain) {
		dev_warn(wm831x->dev, "Failed to allocate IRQ domain\n");
		return -EINVAL;
	}

	if (pdata->irq_cmos)
		i = 0;
	else
		i = WM831X_IRQ_OD;

	wm831x_set_bits(wm831x, WM831X_IRQ_CONFIG,
			WM831X_IRQ_OD, i);

	wm831x->irq = irq;
	wm831x->irq_domain = domain;

	if (irq) {
		/* Try to flag /IRQ as a wake source; there are a number of
		 * unconditional wake sources in the PMIC so this isn't
		 * conditional but we don't actually care *too* much if it
		 * fails.
		 */
		ret = enable_irq_wake(irq);
		if (ret != 0) {
			dev_warn(wm831x->dev,
				 "Can't enable IRQ as wake source: %d\n",
				 ret);
		}

		ret = request_threaded_irq(irq, NULL, wm831x_irq_thread,
					   IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					   "wm831x", wm831x);
		if (ret != 0) {
			dev_err(wm831x->dev, "Failed to request IRQ %d: %d\n",
				irq, ret);
			return ret;
		}
	} else {
		dev_warn(wm831x->dev,
			 "No interrupt specified - functionality limited\n");
	}

	/* Enable top level interrupts, we mask at secondary level */
	wm831x_reg_write(wm831x, WM831X_SYSTEM_INTERRUPTS_MASK, 0);

	return 0;
}