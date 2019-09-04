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
struct hfi1_devdata {int num_sdma; int /*<<< orphan*/ * per_sdma; int /*<<< orphan*/  sdma_unfreeze_count; } ;
typedef  enum sdma_events { ____Placeholder_sdma_events } sdma_events ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int sdma_event_e80_hw_freeze ; 
 int sdma_event_e85_link_down ; 
 int /*<<< orphan*/  sdma_process_event (int /*<<< orphan*/ *,int) ; 

void sdma_freeze_notify(struct hfi1_devdata *dd, int link_down)
{
	int i;
	enum sdma_events event = link_down ? sdma_event_e85_link_down :
					     sdma_event_e80_hw_freeze;

	/* set up the wait but do not wait here */
	atomic_set(&dd->sdma_unfreeze_count, dd->num_sdma);

	/* tell all engines to stop running and wait */
	for (i = 0; i < dd->num_sdma; i++)
		sdma_process_event(&dd->per_sdma[i], event);

	/* sdma_freeze() will wait for all engines to have stopped */
}