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
struct TYPE_2__ {scalar_t__ irq; scalar_t__ handle_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_PERCPU ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmc_reserve_mutex ; 
 int request_irq (scalar_t__,scalar_t__,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* riscv_pmu ; 

__attribute__((used)) static int reserve_pmc_hardware(void)
{
	int err = 0;

	mutex_lock(&pmc_reserve_mutex);
	if (riscv_pmu->irq >= 0 && riscv_pmu->handle_irq) {
		err = request_irq(riscv_pmu->irq, riscv_pmu->handle_irq,
				  IRQF_PERCPU, "riscv-base-perf", NULL);
	}
	mutex_unlock(&pmc_reserve_mutex);

	return err;
}