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
struct adapter {int flags; TYPE_2__* pdev; TYPE_1__* msix_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  vec; } ;

/* Variables and functions */
 int CXGB4_FULL_INIT_DONE ; 
 int CXGB4_USING_MSIX ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct adapter*) ; 
 int /*<<< orphan*/  free_msix_queue_irqs (struct adapter*) ; 
 int /*<<< orphan*/  quiesce_rx (struct adapter*) ; 
 int /*<<< orphan*/  t4_intr_disable (struct adapter*) ; 

__attribute__((used)) static void disable_interrupts(struct adapter *adap)
{
	if (adap->flags & CXGB4_FULL_INIT_DONE) {
		t4_intr_disable(adap);
		if (adap->flags & CXGB4_USING_MSIX) {
			free_msix_queue_irqs(adap);
			free_irq(adap->msix_info[0].vec, adap);
		} else {
			free_irq(adap->pdev->irq, adap);
		}
		quiesce_rx(adap);
	}
}