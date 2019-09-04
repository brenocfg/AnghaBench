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
struct edma_cc {int num_channels; int num_slots; int /*<<< orphan*/  id; int /*<<< orphan*/  slot_inuse; scalar_t__ chmap_exist; } ;

/* Variables and functions */
 int EBUSY ; 
 int EDMA_CHAN_SLOT (int) ; 
 int EDMA_CTLR_CHAN (int /*<<< orphan*/ ,int) ; 
 int EDMA_SLOT_ANY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dummy_paramset ; 
 int /*<<< orphan*/  edma_write_slot (struct edma_cc*,int,int /*<<< orphan*/ *) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int edma_alloc_slot(struct edma_cc *ecc, int slot)
{
	if (slot >= 0) {
		slot = EDMA_CHAN_SLOT(slot);
		/* Requesting entry paRAM slot for a HW triggered channel. */
		if (ecc->chmap_exist && slot < ecc->num_channels)
			slot = EDMA_SLOT_ANY;
	}

	if (slot < 0) {
		if (ecc->chmap_exist)
			slot = 0;
		else
			slot = ecc->num_channels;
		for (;;) {
			slot = find_next_zero_bit(ecc->slot_inuse,
						  ecc->num_slots,
						  slot);
			if (slot == ecc->num_slots)
				return -ENOMEM;
			if (!test_and_set_bit(slot, ecc->slot_inuse))
				break;
		}
	} else if (slot >= ecc->num_slots) {
		return -EINVAL;
	} else if (test_and_set_bit(slot, ecc->slot_inuse)) {
		return -EBUSY;
	}

	edma_write_slot(ecc, slot, &dummy_paramset);

	return EDMA_CTLR_CHAN(ecc->id, slot);
}