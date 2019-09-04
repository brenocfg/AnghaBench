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
typedef  int /*<<< orphan*/  u32 ;
struct et131x_adapter {scalar_t__ flow; TYPE_2__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  int_mask; } ;
struct TYPE_4__ {TYPE_1__ global; } ;

/* Variables and functions */
 scalar_t__ FLOW_BOTH ; 
 scalar_t__ FLOW_TXONLY ; 
 int /*<<< orphan*/  INT_MASK_ENABLE ; 
 int /*<<< orphan*/  INT_MASK_ENABLE_NO_FLOW ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void et131x_enable_interrupts(struct et131x_adapter *adapter)
{
	u32 mask;

	if (adapter->flow == FLOW_TXONLY || adapter->flow == FLOW_BOTH)
		mask = INT_MASK_ENABLE;
	else
		mask = INT_MASK_ENABLE_NO_FLOW;

	writel(mask, &adapter->regs->global.int_mask);
}