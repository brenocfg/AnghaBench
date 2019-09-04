#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ksz_hw_desc {int dummy; } ;
struct ksz_desc_info {int alloc; int avail; struct ksz_desc* ring; struct ksz_desc* cur; scalar_t__ next; scalar_t__ last; int /*<<< orphan*/  ring_phys; scalar_t__ size; struct ksz_hw_desc* ring_virt; } ;
struct TYPE_6__ {int end_of_ring; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; TYPE_1__ rx; } ;
struct TYPE_10__ {TYPE_4__ buf; } ;
struct ksz_desc {TYPE_5__ sw; TYPE_3__* phw; } ;
struct TYPE_7__ {void* data; } ;
struct TYPE_8__ {TYPE_2__ buf; void* next; } ;

/* Variables and functions */
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hw_init_desc(struct ksz_desc_info *desc_info, int transmit)
{
	int i;
	u32 phys = desc_info->ring_phys;
	struct ksz_hw_desc *desc = desc_info->ring_virt;
	struct ksz_desc *cur = desc_info->ring;
	struct ksz_desc *previous = NULL;

	for (i = 0; i < desc_info->alloc; i++) {
		cur->phw = desc++;
		phys += desc_info->size;
		previous = cur++;
		previous->phw->next = cpu_to_le32(phys);
	}
	previous->phw->next = cpu_to_le32(desc_info->ring_phys);
	previous->sw.buf.rx.end_of_ring = 1;
	previous->phw->buf.data = cpu_to_le32(previous->sw.buf.data);

	desc_info->avail = desc_info->alloc;
	desc_info->last = desc_info->next = 0;

	desc_info->cur = desc_info->ring;
}