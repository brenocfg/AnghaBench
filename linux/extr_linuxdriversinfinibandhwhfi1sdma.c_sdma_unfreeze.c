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
struct hfi1_devdata {int num_sdma; int /*<<< orphan*/ * per_sdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdma_event_e82_hw_unfreeze ; 
 int /*<<< orphan*/  sdma_process_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sdma_unfreeze(struct hfi1_devdata *dd)
{
	int i;

	/* tell all engines start freeze clean up */
	for (i = 0; i < dd->num_sdma; i++)
		sdma_process_event(&dd->per_sdma[i],
				   sdma_event_e82_hw_unfreeze);
}