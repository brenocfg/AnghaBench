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
struct tb_nhi {int hop_count; TYPE_2__* ops; int /*<<< orphan*/  msix_ida; int /*<<< orphan*/  interrupt_work; TYPE_1__* pdev; scalar_t__* rx_rings; scalar_t__* tx_rings; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* shutdown ) (struct tb_nhi*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  msix_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tb_nhi*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nhi_disable_interrupts (struct tb_nhi*) ; 
 int /*<<< orphan*/  stub1 (struct tb_nhi*) ; 

__attribute__((used)) static void nhi_shutdown(struct tb_nhi *nhi)
{
	int i;

	dev_dbg(&nhi->pdev->dev, "shutdown\n");

	for (i = 0; i < nhi->hop_count; i++) {
		if (nhi->tx_rings[i])
			dev_WARN(&nhi->pdev->dev,
				 "TX ring %d is still active\n", i);
		if (nhi->rx_rings[i])
			dev_WARN(&nhi->pdev->dev,
				 "RX ring %d is still active\n", i);
	}
	nhi_disable_interrupts(nhi);
	/*
	 * We have to release the irq before calling flush_work. Otherwise an
	 * already executing IRQ handler could call schedule_work again.
	 */
	if (!nhi->pdev->msix_enabled) {
		devm_free_irq(&nhi->pdev->dev, nhi->pdev->irq, nhi);
		flush_work(&nhi->interrupt_work);
	}
	ida_destroy(&nhi->msix_ida);

	if (nhi->ops && nhi->ops->shutdown)
		nhi->ops->shutdown(nhi);
}