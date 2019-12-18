#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cx88_core {int /*<<< orphan*/  pci_irqmask; struct cx88_IR* ir; } ;
struct TYPE_3__ {int /*<<< orphan*/  function; } ;
struct cx88_IR {int polling; scalar_t__ sampling; TYPE_1__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int EINVAL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  MO_DDSCFG_IO ; 
 int /*<<< orphan*/  MO_DDS_IO ; 
 int /*<<< orphan*/  PCI_INT_IR_SMPINT ; 
 int /*<<< orphan*/  cx88_ir_work ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ir_samplerate ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __cx88_ir_start(void *priv)
{
	struct cx88_core *core = priv;
	struct cx88_IR *ir;

	if (!core || !core->ir)
		return -EINVAL;

	ir = core->ir;

	if (ir->polling) {
		hrtimer_init(&ir->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
		ir->timer.function = cx88_ir_work;
		hrtimer_start(&ir->timer,
			      ktime_set(0, ir->polling * 1000000),
			      HRTIMER_MODE_REL);
	}
	if (ir->sampling) {
		core->pci_irqmask |= PCI_INT_IR_SMPINT;
		cx_write(MO_DDS_IO, 0x33F286 * ir_samplerate); /* samplerate */
		cx_write(MO_DDSCFG_IO, 0x5); /* enable */
	}
	return 0;
}