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
typedef  size_t uint8_t ;
typedef  int uint64_t ;
struct qxl_memslot {unsigned long start_phys_addr; unsigned long end_phys_addr; int generation; int high_bits; } ;
struct qxl_device {size_t slot_gen_bits; int slot_id_bits; TYPE_1__* rom; struct qxl_memslot* mem_slots; } ;
struct TYPE_2__ {size_t slots_start; int slot_generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  setup_hw_slot (struct qxl_device*,size_t,struct qxl_memslot*) ; 

__attribute__((used)) static uint8_t setup_slot(struct qxl_device *qdev, uint8_t slot_index_offset,
	unsigned long start_phys_addr, unsigned long end_phys_addr)
{
	uint64_t high_bits;
	struct qxl_memslot *slot;
	uint8_t slot_index;

	slot_index = qdev->rom->slots_start + slot_index_offset;
	slot = &qdev->mem_slots[slot_index];
	slot->start_phys_addr = start_phys_addr;
	slot->end_phys_addr = end_phys_addr;

	setup_hw_slot(qdev, slot_index, slot);

	slot->generation = qdev->rom->slot_generation;
	high_bits = slot_index << qdev->slot_gen_bits;
	high_bits |= slot->generation;
	high_bits <<= (64 - (qdev->slot_gen_bits + qdev->slot_id_bits));
	slot->high_bits = high_bits;
	return slot_index;
}