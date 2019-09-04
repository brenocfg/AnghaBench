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
struct mtip_work {int completed; int /*<<< orphan*/  work; int /*<<< orphan*/  cpu_binding; } ;
struct mtip_port {scalar_t__* completed; scalar_t__ mmio; } ;
struct driver_data {scalar_t__ mmio; int /*<<< orphan*/  dd_flag; int /*<<< orphan*/  pdev; struct mtip_work* work; int /*<<< orphan*/  isr_workq; int /*<<< orphan*/  irq_workers_active; struct mtip_port* port; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 scalar_t__ HOST_IRQ_STAT ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  MTIP_DDF_REMOVE_PENDING_BIT ; 
 int MTIP_MAX_SLOT_GROUPS ; 
 int PORT_IRQ_ERR ; 
 int PORT_IRQ_LEGACY ; 
 int PORT_IRQ_SDB_FIS ; 
 scalar_t__ PORT_IRQ_STAT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ likely (int) ; 
 int mtip_check_surprise_removal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtip_process_errors (struct driver_data*,int) ; 
 int /*<<< orphan*/  mtip_process_legacy (struct driver_data*,int) ; 
 int /*<<< orphan*/  mtip_workq_sdbfx (struct mtip_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* readl (scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline irqreturn_t mtip_handle_irq(struct driver_data *data)
{
	struct driver_data *dd = (struct driver_data *) data;
	struct mtip_port *port = dd->port;
	u32 hba_stat, port_stat;
	int rv = IRQ_NONE;
	int do_irq_enable = 1, i, workers;
	struct mtip_work *twork;

	hba_stat = readl(dd->mmio + HOST_IRQ_STAT);
	if (hba_stat) {
		rv = IRQ_HANDLED;

		/* Acknowledge the interrupt status on the port.*/
		port_stat = readl(port->mmio + PORT_IRQ_STAT);
		if (unlikely(port_stat == 0xFFFFFFFF)) {
			mtip_check_surprise_removal(dd->pdev);
			return IRQ_HANDLED;
		}
		writel(port_stat, port->mmio + PORT_IRQ_STAT);

		/* Demux port status */
		if (likely(port_stat & PORT_IRQ_SDB_FIS)) {
			do_irq_enable = 0;
			WARN_ON_ONCE(atomic_read(&dd->irq_workers_active) != 0);

			/* Start at 1: group zero is always local? */
			for (i = 0, workers = 0; i < MTIP_MAX_SLOT_GROUPS;
									i++) {
				twork = &dd->work[i];
				twork->completed = readl(port->completed[i]);
				if (twork->completed)
					workers++;
			}

			atomic_set(&dd->irq_workers_active, workers);
			if (workers) {
				for (i = 1; i < MTIP_MAX_SLOT_GROUPS; i++) {
					twork = &dd->work[i];
					if (twork->completed)
						queue_work_on(
							twork->cpu_binding,
							dd->isr_workq,
							&twork->work);
				}

				if (likely(dd->work[0].completed))
					mtip_workq_sdbfx(port, 0,
							dd->work[0].completed);

			} else {
				/*
				 * Chip quirk: SDB interrupt but nothing
				 * to complete
				 */
				do_irq_enable = 1;
			}
		}

		if (unlikely(port_stat & PORT_IRQ_ERR)) {
			if (unlikely(mtip_check_surprise_removal(dd->pdev))) {
				/* don't proceed further */
				return IRQ_HANDLED;
			}
			if (test_bit(MTIP_DDF_REMOVE_PENDING_BIT,
							&dd->dd_flag))
				return rv;

			mtip_process_errors(dd, port_stat & PORT_IRQ_ERR);
		}

		if (unlikely(port_stat & PORT_IRQ_LEGACY))
			mtip_process_legacy(dd, port_stat & PORT_IRQ_LEGACY);
	}

	/* acknowledge interrupt */
	if (unlikely(do_irq_enable))
		writel(hba_stat, dd->mmio + HOST_IRQ_STAT);

	return rv;
}