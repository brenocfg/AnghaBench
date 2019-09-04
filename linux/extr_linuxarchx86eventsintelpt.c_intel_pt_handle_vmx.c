#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct perf_event* event; } ;
struct pt {TYPE_3__ handle; int /*<<< orphan*/  vmx_on; } ;
struct TYPE_4__ {int /*<<< orphan*/  config; } ;
struct perf_event {TYPE_1__ hw; } ;
struct TYPE_5__ {scalar_t__ vmx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_RTIT_CTL ; 
 int /*<<< orphan*/  PERF_AUX_FLAG_PARTIAL ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  perf_aux_output_flag (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_ctx ; 
 TYPE_2__ pt_pmu ; 
 struct pt* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void intel_pt_handle_vmx(int on)
{
	struct pt *pt = this_cpu_ptr(&pt_ctx);
	struct perf_event *event;
	unsigned long flags;

	/* PT plays nice with VMX, do nothing */
	if (pt_pmu.vmx)
		return;

	/*
	 * VMXON will clear RTIT_CTL.TraceEn; we need to make
	 * sure to not try to set it while VMX is on. Disable
	 * interrupts to avoid racing with pmu callbacks;
	 * concurrent PMI should be handled fine.
	 */
	local_irq_save(flags);
	WRITE_ONCE(pt->vmx_on, on);

	/*
	 * If an AUX transaction is in progress, it will contain
	 * gap(s), so flag it PARTIAL to inform the user.
	 */
	event = pt->handle.event;
	if (event)
		perf_aux_output_flag(&pt->handle,
		                     PERF_AUX_FLAG_PARTIAL);

	/* Turn PTs back on */
	if (!on && event)
		wrmsrl(MSR_IA32_RTIT_CTL, event->hw.config);

	local_irq_restore(flags);
}