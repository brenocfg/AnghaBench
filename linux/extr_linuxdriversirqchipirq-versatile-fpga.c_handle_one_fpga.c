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
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;
struct fpga_irq_data {int /*<<< orphan*/  domain; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ IRQ_STATUS ; 
 int ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_domain_irq (int /*<<< orphan*/ ,int,struct pt_regs*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int handle_one_fpga(struct fpga_irq_data *f, struct pt_regs *regs)
{
	int handled = 0;
	int irq;
	u32 status;

	while ((status  = readl(f->base + IRQ_STATUS))) {
		irq = ffs(status) - 1;
		handle_domain_irq(f->domain, irq, regs);
		handled = 1;
	}

	return handled;
}