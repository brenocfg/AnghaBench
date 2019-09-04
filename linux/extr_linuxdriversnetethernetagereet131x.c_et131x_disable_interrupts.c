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
struct et131x_adapter {TYPE_2__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  int_mask; } ;
struct TYPE_4__ {TYPE_1__ global; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MASK_DISABLE ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void et131x_disable_interrupts(struct et131x_adapter *adapter)
{
	writel(INT_MASK_DISABLE, &adapter->regs->global.int_mask);
}