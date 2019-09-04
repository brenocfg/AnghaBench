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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;
struct alx_priv {TYPE_1__ hw; int /*<<< orphan*/  dev; int /*<<< orphan*/  num_rxq; int /*<<< orphan*/  num_txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_ISR ; 
 scalar_t__ ALX_ISR_DIS ; 
 int alx_alloc_napis (struct alx_priv*) ; 
 int alx_alloc_rings (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_configure (struct alx_priv*) ; 
 int alx_enable_msix (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_free_napis (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_free_rings (struct alx_priv*) ; 
 int alx_init_intr (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_irq_enable (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_reinit_rings (struct alx_priv*) ; 
 int alx_request_irq (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_schedule_link_check (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_write_mem32 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_real_num_rx_queues (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __alx_open(struct alx_priv *alx, bool resume)
{
	int err;

	err = alx_enable_msix(alx);
	if (err < 0) {
		err = alx_init_intr(alx);
		if (err)
			return err;
	}

	if (!resume)
		netif_carrier_off(alx->dev);

	err = alx_alloc_napis(alx);
	if (err)
		goto out_disable_adv_intr;

	err = alx_alloc_rings(alx);
	if (err)
		goto out_free_rings;

	alx_configure(alx);

	err = alx_request_irq(alx);
	if (err)
		goto out_free_rings;

	/* must be called after alx_request_irq because the chip stops working
	 * if we copy the dma addresses in alx_init_ring_ptrs twice when
	 * requesting msi-x interrupts failed
	 */
	alx_reinit_rings(alx);

	netif_set_real_num_tx_queues(alx->dev, alx->num_txq);
	netif_set_real_num_rx_queues(alx->dev, alx->num_rxq);

	/* clear old interrupts */
	alx_write_mem32(&alx->hw, ALX_ISR, ~(u32)ALX_ISR_DIS);

	alx_irq_enable(alx);

	if (!resume)
		netif_tx_start_all_queues(alx->dev);

	alx_schedule_link_check(alx);
	return 0;

out_free_rings:
	alx_free_rings(alx);
	alx_free_napis(alx);
out_disable_adv_intr:
	pci_free_irq_vectors(alx->hw.pdev);
	return err;
}