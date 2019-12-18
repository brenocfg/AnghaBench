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
typedef  int uint64_t ;
struct qxl_memslot {unsigned int index; char const* name; unsigned long start_phys_addr; unsigned long size; int generation; int high_bits; scalar_t__ gpu_offset; } ;
struct qxl_device {TYPE_1__* rom; } ;
struct TYPE_2__ {int slot_generation; int slots_start; int slot_gen_bits; int slot_id_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,int,char const*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  setup_hw_slot (struct qxl_device*,struct qxl_memslot*) ; 

__attribute__((used)) static void setup_slot(struct qxl_device *qdev,
		       struct qxl_memslot *slot,
		       unsigned int slot_index,
		       const char *slot_name,
		       unsigned long start_phys_addr,
		       unsigned long size)
{
	uint64_t high_bits;

	slot->index = slot_index;
	slot->name = slot_name;
	slot->start_phys_addr = start_phys_addr;
	slot->size = size;

	setup_hw_slot(qdev, slot);

	slot->generation = qdev->rom->slot_generation;
	high_bits = (qdev->rom->slots_start + slot->index)
		<< qdev->rom->slot_gen_bits;
	high_bits |= slot->generation;
	high_bits <<= (64 - (qdev->rom->slot_gen_bits + qdev->rom->slot_id_bits));
	slot->high_bits = high_bits;

	DRM_INFO("slot %d (%s): base 0x%08lx, size 0x%08lx, gpu_offset 0x%lx\n",
		 slot->index, slot->name,
		 (unsigned long)slot->start_phys_addr,
		 (unsigned long)slot->size,
		 (unsigned long)slot->gpu_offset);
}