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
struct TYPE_2__ {int* irq_warn_once; } ;
struct intel_vgpu {TYPE_1__ irq; int /*<<< orphan*/  id; } ;
struct intel_gvt_irq {int dummy; } ;
typedef  enum intel_gvt_event_type { ____Placeholder_intel_gvt_event_type } intel_gvt_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  gvt_dbg_core (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * irq_name ; 
 int /*<<< orphan*/  propagate_event (struct intel_gvt_irq*,int,struct intel_vgpu*) ; 

__attribute__((used)) static void handle_default_event_virt(struct intel_gvt_irq *irq,
	enum intel_gvt_event_type event, struct intel_vgpu *vgpu)
{
	if (!vgpu->irq.irq_warn_once[event]) {
		gvt_dbg_core("vgpu%d: IRQ receive event %d (%s)\n",
			vgpu->id, event, irq_name[event]);
		vgpu->irq.irq_warn_once[event] = true;
	}
	propagate_event(irq, event, vgpu);
}