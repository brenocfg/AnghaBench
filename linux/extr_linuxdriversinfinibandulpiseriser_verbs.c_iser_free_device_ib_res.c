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
struct iser_device {int comps_used; int /*<<< orphan*/ * pd; struct iser_comp* comps; int /*<<< orphan*/  event_handler; } ;
struct iser_comp {int /*<<< orphan*/ * cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dealloc_pd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_free_cq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct iser_comp*) ; 

__attribute__((used)) static void iser_free_device_ib_res(struct iser_device *device)
{
	int i;

	for (i = 0; i < device->comps_used; i++) {
		struct iser_comp *comp = &device->comps[i];

		ib_free_cq(comp->cq);
		comp->cq = NULL;
	}

	ib_unregister_event_handler(&device->event_handler);
	ib_dealloc_pd(device->pd);

	kfree(device->comps);
	device->comps = NULL;
	device->pd = NULL;
}