#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qxl_memslot {int /*<<< orphan*/  end_phys_addr; int /*<<< orphan*/  start_phys_addr; } ;
struct qxl_device {TYPE_2__* ram_header; } ;
struct TYPE_3__ {int /*<<< orphan*/  mem_end; int /*<<< orphan*/  mem_start; } ;
struct TYPE_4__ {TYPE_1__ mem_slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  qxl_io_memslot_add (struct qxl_device*,int) ; 

__attribute__((used)) static void setup_hw_slot(struct qxl_device *qdev, int slot_index,
			  struct qxl_memslot *slot)
{
	qdev->ram_header->mem_slot.mem_start = slot->start_phys_addr;
	qdev->ram_header->mem_slot.mem_end = slot->end_phys_addr;
	qxl_io_memslot_add(qdev, slot_index);
}