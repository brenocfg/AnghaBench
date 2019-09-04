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
struct TYPE_3__ {scalar_t__ irq; } ;

/* Variables and functions */
 int ENOENT ; 
 int IRQF_NOBALANCING ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_NO_THREAD ; 
 int IRQF_PERCPU ; 
 int IRQF_SHARED ; 
 scalar_t__ cp0_perfcount_irq ; 
 TYPE_1__ mipspmu ; 
 int /*<<< orphan*/  mipsxx_pmu_handle_irq ; 
 int /*<<< orphan*/  mipsxx_pmu_handle_shared_irq ; 
 int /*<<< orphan*/  perf_irq ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  save_perf_irq ; 

__attribute__((used)) static int mipspmu_get_irq(void)
{
	int err;

	if (mipspmu.irq >= 0) {
		/* Request my own irq handler. */
		err = request_irq(mipspmu.irq, mipsxx_pmu_handle_irq,
				  IRQF_PERCPU | IRQF_NOBALANCING |
				  IRQF_NO_THREAD | IRQF_NO_SUSPEND |
				  IRQF_SHARED,
				  "mips_perf_pmu", &mipspmu);
		if (err) {
			pr_warn("Unable to request IRQ%d for MIPS performance counters!\n",
				mipspmu.irq);
		}
	} else if (cp0_perfcount_irq < 0) {
		/*
		 * We are sharing the irq number with the timer interrupt.
		 */
		save_perf_irq = perf_irq;
		perf_irq = mipsxx_pmu_handle_shared_irq;
		err = 0;
	} else {
		pr_warn("The platform hasn't properly defined its interrupt controller\n");
		err = -ENOENT;
	}

	return err;
}