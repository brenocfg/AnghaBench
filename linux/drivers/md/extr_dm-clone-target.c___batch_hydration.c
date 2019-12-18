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
struct dm_clone_region_hydration {scalar_t__ region_nr; int /*<<< orphan*/  list; struct clone* clone; } ;
struct clone {int /*<<< orphan*/  hydration_batch_size; } ;
struct batch_info {unsigned int nr_batched_regions; struct dm_clone_region_hydration* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hydration_copy (struct dm_clone_region_hydration*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __batch_hydration(struct batch_info *batch,
			      struct dm_clone_region_hydration *hd)
{
	struct clone *clone = hd->clone;
	unsigned int max_batch_size = READ_ONCE(clone->hydration_batch_size);

	if (batch->head) {
		/* Try to extend the current batch */
		if (batch->nr_batched_regions < max_batch_size &&
		    (batch->head->region_nr + batch->nr_batched_regions) == hd->region_nr) {
			list_add_tail(&hd->list, &batch->head->list);
			batch->nr_batched_regions++;
			hd = NULL;
		}

		/* Check if we should issue the current batch */
		if (batch->nr_batched_regions >= max_batch_size || hd) {
			hydration_copy(batch->head, batch->nr_batched_regions);
			batch->head = NULL;
			batch->nr_batched_regions = 0;
		}
	}

	if (!hd)
		return;

	/* We treat max batch sizes of zero and one equivalently */
	if (max_batch_size <= 1) {
		hydration_copy(hd, 1);
		return;
	}

	/* Start a new batch */
	BUG_ON(!list_empty(&hd->list));
	batch->head = hd;
	batch->nr_batched_regions = 1;
}