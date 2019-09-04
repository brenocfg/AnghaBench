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
struct edma_cc {unsigned int num_slots; int /*<<< orphan*/  slot_inuse; } ;

/* Variables and functions */
 unsigned int EDMA_CHAN_SLOT (unsigned int) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dummy_paramset ; 
 int /*<<< orphan*/  edma_write_slot (struct edma_cc*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void edma_free_slot(struct edma_cc *ecc, unsigned slot)
{
	slot = EDMA_CHAN_SLOT(slot);
	if (slot >= ecc->num_slots)
		return;

	edma_write_slot(ecc, slot, &dummy_paramset);
	clear_bit(slot, ecc->slot_inuse);
}