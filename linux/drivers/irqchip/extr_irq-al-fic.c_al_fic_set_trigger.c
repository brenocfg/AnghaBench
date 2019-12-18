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
typedef  int /*<<< orphan*/  u32 ;
struct irq_chip_generic {TYPE_1__* chip_types; } ;
struct al_fic {int state; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irq_flow_handler_t ;
typedef  enum al_fic_state { ____Placeholder_al_fic_state } al_fic_state ;
struct TYPE_2__ {int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int AL_FIC_CONFIGURED_LEVEL ; 
 scalar_t__ AL_FIC_CONTROL ; 
 int /*<<< orphan*/  CONTROL_TRIGGER_RISING ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void al_fic_set_trigger(struct al_fic *fic,
			       struct irq_chip_generic *gc,
			       enum al_fic_state new_state)
{
	irq_flow_handler_t handler;
	u32 control = readl_relaxed(fic->base + AL_FIC_CONTROL);

	if (new_state == AL_FIC_CONFIGURED_LEVEL) {
		handler = handle_level_irq;
		control &= ~CONTROL_TRIGGER_RISING;
	} else {
		handler = handle_edge_irq;
		control |= CONTROL_TRIGGER_RISING;
	}
	gc->chip_types->handler = handler;
	fic->state = new_state;
	writel_relaxed(control, fic->base + AL_FIC_CONTROL);
}