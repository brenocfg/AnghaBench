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
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  VALID_EVTCHN (unsigned int) ; 
 unsigned int evtchn_from_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_evtchn (unsigned int) ; 
 int test_and_set_mask (unsigned int) ; 
 int /*<<< orphan*/  unmask_evtchn (unsigned int) ; 

__attribute__((used)) static int retrigger_dynirq(struct irq_data *data)
{
	unsigned int evtchn = evtchn_from_irq(data->irq);
	int masked;

	if (!VALID_EVTCHN(evtchn))
		return 0;

	masked = test_and_set_mask(evtchn);
	set_evtchn(evtchn);
	if (!masked)
		unmask_evtchn(evtchn);

	return 1;
}