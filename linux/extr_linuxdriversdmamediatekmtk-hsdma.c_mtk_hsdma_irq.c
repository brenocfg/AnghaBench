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
struct mtk_hsdma_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MTK_HSDMA_INT_ENABLE ; 
 int /*<<< orphan*/  MTK_HSDMA_INT_RXDONE ; 
 int /*<<< orphan*/  mtk_dma_clr (struct mtk_hsdma_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hsdma_free_rooms_in_ring (struct mtk_hsdma_device*) ; 

__attribute__((used)) static irqreturn_t mtk_hsdma_irq(int irq, void *devid)
{
	struct mtk_hsdma_device *hsdma = devid;

	/*
	 * Disable interrupt until all completed PDs are cleaned up in
	 * mtk_hsdma_free_rooms call.
	 */
	mtk_dma_clr(hsdma, MTK_HSDMA_INT_ENABLE, MTK_HSDMA_INT_RXDONE);

	mtk_hsdma_free_rooms_in_ring(hsdma);

	return IRQ_HANDLED;
}