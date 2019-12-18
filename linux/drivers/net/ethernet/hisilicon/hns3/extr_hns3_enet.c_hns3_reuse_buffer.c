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
struct hns3_enet_ring {TYPE_2__* desc; TYPE_3__* desc_cb; } ;
struct TYPE_6__ {scalar_t__ page_offset; scalar_t__ dma; scalar_t__ reuse_flag; } ;
struct TYPE_4__ {scalar_t__ bd_base_info; } ;
struct TYPE_5__ {TYPE_1__ rx; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 

__attribute__((used)) static void hns3_reuse_buffer(struct hns3_enet_ring *ring, int i)
{
	ring->desc_cb[i].reuse_flag = 0;
	ring->desc[i].addr = cpu_to_le64(ring->desc_cb[i].dma +
					 ring->desc_cb[i].page_offset);
	ring->desc[i].rx.bd_base_info = 0;
}