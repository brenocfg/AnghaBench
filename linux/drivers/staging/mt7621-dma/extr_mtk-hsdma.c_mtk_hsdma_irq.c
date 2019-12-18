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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mtk_hsdam_engine {TYPE_1__ ddev; int /*<<< orphan*/  task; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int HSDMA_INT_RX_Q0 ; 
 int /*<<< orphan*/  HSDMA_REG_INT_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ likely (int) ; 
 int mtk_hsdma_read (struct mtk_hsdam_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hsdma_write (struct mtk_hsdam_engine*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t mtk_hsdma_irq(int irq, void *devid)
{
	struct mtk_hsdam_engine *hsdma = devid;
	u32 status;

	status = mtk_hsdma_read(hsdma, HSDMA_REG_INT_STATUS);
	if (unlikely(!status))
		return IRQ_NONE;

	if (likely(status & HSDMA_INT_RX_Q0))
		tasklet_schedule(&hsdma->task);
	else
		dev_dbg(hsdma->ddev.dev, "unhandle irq status %08x\n", status);
	/* clean intr bits */
	mtk_hsdma_write(hsdma, HSDMA_REG_INT_STATUS, status);

	return IRQ_HANDLED;
}