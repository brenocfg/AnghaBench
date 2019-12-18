#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qxl_memslot {scalar_t__ index; scalar_t__ size; scalar_t__ start_phys_addr; } ;
struct qxl_device {TYPE_3__* rom; TYPE_2__* ram_header; } ;
struct TYPE_6__ {scalar_t__ slots_start; } ;
struct TYPE_4__ {scalar_t__ mem_end; scalar_t__ mem_start; } ;
struct TYPE_5__ {TYPE_1__ mem_slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  qxl_io_memslot_add (struct qxl_device*,scalar_t__) ; 

__attribute__((used)) static void setup_hw_slot(struct qxl_device *qdev, struct qxl_memslot *slot)
{
	qdev->ram_header->mem_slot.mem_start = slot->start_phys_addr;
	qdev->ram_header->mem_slot.mem_end = slot->start_phys_addr + slot->size;
	qxl_io_memslot_add(qdev, qdev->rom->slots_start + slot->index);
}