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
struct intel_gvt_irq {TYPE_1__* events; } ;
struct TYPE_2__ {int /*<<< orphan*/  v_handler; int /*<<< orphan*/ * info; } ;

/* Variables and functions */
 int INTEL_GVT_EVENT_MAX ; 
 int /*<<< orphan*/  handle_default_event_virt ; 

__attribute__((used)) static void init_events(
	struct intel_gvt_irq *irq)
{
	int i;

	for (i = 0; i < INTEL_GVT_EVENT_MAX; i++) {
		irq->events[i].info = NULL;
		irq->events[i].v_handler = handle_default_event_virt;
	}
}