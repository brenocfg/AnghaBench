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
struct mt76_queue {TYPE_1__* regs; int /*<<< orphan*/  head; } ;
struct mt76_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt76_dma_kick_queue(struct mt76_dev *dev, struct mt76_queue *q)
{
	writel(q->head, &q->regs->cpu_idx);
}