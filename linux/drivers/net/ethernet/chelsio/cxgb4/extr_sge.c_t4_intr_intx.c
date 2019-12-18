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
struct adapter {int flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CXGB4_MASTER_PF ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_PF_CLI_A ; 
 int process_intrq (struct adapter*) ; 
 scalar_t__ t4_slow_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t t4_intr_intx(int irq, void *cookie)
{
	struct adapter *adap = cookie;

	t4_write_reg(adap, MYPF_REG(PCIE_PF_CLI_A), 0);
	if (((adap->flags & CXGB4_MASTER_PF) && t4_slow_intr_handler(adap)) |
	    process_intrq(adap))
		return IRQ_HANDLED;
	return IRQ_NONE;             /* probably shared interrupt */
}