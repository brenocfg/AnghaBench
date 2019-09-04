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
struct isert_device {int comps_used; struct isert_comp* comps; } ;
struct isert_comp {scalar_t__ cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_free_cq (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct isert_comp*) ; 

__attribute__((used)) static void
isert_free_comps(struct isert_device *device)
{
	int i;

	for (i = 0; i < device->comps_used; i++) {
		struct isert_comp *comp = &device->comps[i];

		if (comp->cq)
			ib_free_cq(comp->cq);
	}
	kfree(device->comps);
}