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
struct greth_private {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRETH_REGORIN (int /*<<< orphan*/ ,int) ; 
 int GRETH_TXEN ; 
 int GRETH_TXI ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void greth_enable_tx_and_irq(struct greth_private *greth)
{
	wmb(); /* BDs must been written to memory before enabling TX */
	GRETH_REGORIN(greth->regs->control, GRETH_TXEN | GRETH_TXI);
}