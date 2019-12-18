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
struct cmdq {int /*<<< orphan*/  clock; scalar_t__ base; } ;

/* Variables and functions */
 int CMDQ_MAX_EVENT ; 
 scalar_t__ CMDQ_SYNC_TOKEN_UPDATE ; 
 int CMDQ_THR_ACTIVE_SLOT_CYCLES ; 
 scalar_t__ CMDQ_THR_SLOT_CYCLES ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cmdq_init(struct cmdq *cmdq)
{
	int i;

	WARN_ON(clk_enable(cmdq->clock) < 0);
	writel(CMDQ_THR_ACTIVE_SLOT_CYCLES, cmdq->base + CMDQ_THR_SLOT_CYCLES);
	for (i = 0; i <= CMDQ_MAX_EVENT; i++)
		writel(i, cmdq->base + CMDQ_SYNC_TOKEN_UPDATE);
	clk_disable(cmdq->clock);
}