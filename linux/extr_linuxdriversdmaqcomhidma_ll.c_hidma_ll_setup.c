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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct hidma_lldev {int nr_tres; int tre_ring_size; int /*<<< orphan*/  msi_support; scalar_t__ evca; int /*<<< orphan*/  evre_dma; scalar_t__ trca; int /*<<< orphan*/  tre_dma; scalar_t__ tre_write_offset; scalar_t__ evre_processed_off; scalar_t__ tre_processed_off; int /*<<< orphan*/  pending_tre_count; } ;

/* Variables and functions */
 scalar_t__ HIDMA_EVCA_IRQ_CLR_REG ; 
 scalar_t__ HIDMA_EVCA_IRQ_EN_REG ; 
 scalar_t__ HIDMA_EVCA_IRQ_STAT_REG ; 
 scalar_t__ HIDMA_EVCA_RING_HIGH_REG ; 
 scalar_t__ HIDMA_EVCA_RING_LEN_REG ; 
 scalar_t__ HIDMA_EVCA_RING_LOW_REG ; 
 int HIDMA_EVRE_SIZE ; 
 scalar_t__ HIDMA_TRCA_RING_HIGH_REG ; 
 scalar_t__ HIDMA_TRCA_RING_LEN_REG ; 
 scalar_t__ HIDMA_TRCA_RING_LOW_REG ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hidma_ll_enable (struct hidma_lldev*) ; 
 int hidma_ll_reset (struct hidma_lldev*) ; 
 int /*<<< orphan*/  hidma_ll_setup_irq (struct hidma_lldev*,int /*<<< orphan*/ ) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int hidma_ll_setup(struct hidma_lldev *lldev)
{
	int rc;
	u64 addr;
	u32 val;
	u32 nr_tres = lldev->nr_tres;

	atomic_set(&lldev->pending_tre_count, 0);
	lldev->tre_processed_off = 0;
	lldev->evre_processed_off = 0;
	lldev->tre_write_offset = 0;

	/* disable interrupts */
	writel(0, lldev->evca + HIDMA_EVCA_IRQ_EN_REG);

	/* clear all pending interrupts */
	val = readl(lldev->evca + HIDMA_EVCA_IRQ_STAT_REG);
	writel(val, lldev->evca + HIDMA_EVCA_IRQ_CLR_REG);

	rc = hidma_ll_reset(lldev);
	if (rc)
		return rc;

	/*
	 * Clear all pending interrupts again.
	 * Otherwise, we observe reset complete interrupts.
	 */
	val = readl(lldev->evca + HIDMA_EVCA_IRQ_STAT_REG);
	writel(val, lldev->evca + HIDMA_EVCA_IRQ_CLR_REG);

	/* disable interrupts again after reset */
	writel(0, lldev->evca + HIDMA_EVCA_IRQ_EN_REG);

	addr = lldev->tre_dma;
	writel(lower_32_bits(addr), lldev->trca + HIDMA_TRCA_RING_LOW_REG);
	writel(upper_32_bits(addr), lldev->trca + HIDMA_TRCA_RING_HIGH_REG);
	writel(lldev->tre_ring_size, lldev->trca + HIDMA_TRCA_RING_LEN_REG);

	addr = lldev->evre_dma;
	writel(lower_32_bits(addr), lldev->evca + HIDMA_EVCA_RING_LOW_REG);
	writel(upper_32_bits(addr), lldev->evca + HIDMA_EVCA_RING_HIGH_REG);
	writel(HIDMA_EVRE_SIZE * nr_tres,
			lldev->evca + HIDMA_EVCA_RING_LEN_REG);

	/* configure interrupts */
	hidma_ll_setup_irq(lldev, lldev->msi_support);

	rc = hidma_ll_enable(lldev);
	if (rc)
		return rc;

	return rc;
}