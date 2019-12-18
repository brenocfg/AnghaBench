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
struct hns3_enet_ring {TYPE_1__* desc; int /*<<< orphan*/ * desc_cb; } ;
struct TYPE_2__ {scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_unmap_buffer (struct hns3_enet_ring*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns3_buffer_detach(struct hns3_enet_ring *ring, int i)
{
	hns3_unmap_buffer(ring, &ring->desc_cb[i]);
	ring->desc[i].addr = 0;
}