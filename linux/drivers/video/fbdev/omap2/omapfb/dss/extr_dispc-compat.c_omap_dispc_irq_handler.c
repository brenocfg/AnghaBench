#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct omap_dispc_isr_data {int mask; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* isr ) (int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  registered_isr ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  irqs; int /*<<< orphan*/  irq_count; } ;
struct TYPE_4__ {int irq_error_mask; int error_irqs; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  error_work; int /*<<< orphan*/  registered_isr; int /*<<< orphan*/  irq_stats_lock; TYPE_1__ irq_stats; } ;

/* Variables and functions */
 int DISPC_MAX_NR_ISRS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  _omap_dispc_set_irqs () ; 
 int /*<<< orphan*/  dispc_clear_irqstatus (int) ; 
 TYPE_2__ dispc_compat ; 
 int dispc_read_irqenable () ; 
 int dispc_read_irqstatus () ; 
 int /*<<< orphan*/  dss_collect_irq_stats (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct omap_dispc_isr_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_irq_status (int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t omap_dispc_irq_handler(int irq, void *arg)
{
	int i;
	u32 irqstatus, irqenable;
	u32 handledirqs = 0;
	u32 unhandled_errors;
	struct omap_dispc_isr_data *isr_data;
	struct omap_dispc_isr_data registered_isr[DISPC_MAX_NR_ISRS];

	spin_lock(&dispc_compat.irq_lock);

	irqstatus = dispc_read_irqstatus();
	irqenable = dispc_read_irqenable();

	/* IRQ is not for us */
	if (!(irqstatus & irqenable)) {
		spin_unlock(&dispc_compat.irq_lock);
		return IRQ_NONE;
	}

#ifdef CONFIG_FB_OMAP2_DSS_COLLECT_IRQ_STATS
	spin_lock(&dispc_compat.irq_stats_lock);
	dispc_compat.irq_stats.irq_count++;
	dss_collect_irq_stats(irqstatus, dispc_compat.irq_stats.irqs);
	spin_unlock(&dispc_compat.irq_stats_lock);
#endif

	print_irq_status(irqstatus);

	/* Ack the interrupt. Do it here before clocks are possibly turned
	 * off */
	dispc_clear_irqstatus(irqstatus);
	/* flush posted write */
	dispc_read_irqstatus();

	/* make a copy and unlock, so that isrs can unregister
	 * themselves */
	memcpy(registered_isr, dispc_compat.registered_isr,
			sizeof(registered_isr));

	spin_unlock(&dispc_compat.irq_lock);

	for (i = 0; i < DISPC_MAX_NR_ISRS; i++) {
		isr_data = &registered_isr[i];

		if (!isr_data->isr)
			continue;

		if (isr_data->mask & irqstatus) {
			isr_data->isr(isr_data->arg, irqstatus);
			handledirqs |= isr_data->mask;
		}
	}

	spin_lock(&dispc_compat.irq_lock);

	unhandled_errors = irqstatus & ~handledirqs & dispc_compat.irq_error_mask;

	if (unhandled_errors) {
		dispc_compat.error_irqs |= unhandled_errors;

		dispc_compat.irq_error_mask &= ~unhandled_errors;
		_omap_dispc_set_irqs();

		schedule_work(&dispc_compat.error_work);
	}

	spin_unlock(&dispc_compat.irq_lock);

	return IRQ_HANDLED;
}