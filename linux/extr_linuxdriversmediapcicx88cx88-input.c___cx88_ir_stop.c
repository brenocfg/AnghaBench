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
struct cx88_core {int /*<<< orphan*/  pci_irqmask; struct cx88_IR* ir; } ;
struct cx88_IR {int /*<<< orphan*/  timer; scalar_t__ polling; scalar_t__ sampling; } ;

/* Variables and functions */
 int /*<<< orphan*/  MO_DDSCFG_IO ; 
 int /*<<< orphan*/  PCI_INT_IR_SMPINT ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __cx88_ir_stop(void *priv)
{
	struct cx88_core *core = priv;
	struct cx88_IR *ir;

	if (!core || !core->ir)
		return;

	ir = core->ir;
	if (ir->sampling) {
		cx_write(MO_DDSCFG_IO, 0x0);
		core->pci_irqmask &= ~PCI_INT_IR_SMPINT;
	}

	if (ir->polling)
		hrtimer_cancel(&ir->timer);
}