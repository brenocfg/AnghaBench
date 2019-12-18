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
struct hns3_enet_ring {struct hns3_desc_cb* desc_cb; } ;
struct hns3_desc_cb {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_buffer_detach (struct hns3_enet_ring*,int) ; 
 int /*<<< orphan*/  hns3_free_buffer (struct hns3_enet_ring*,struct hns3_desc_cb*) ; 

__attribute__((used)) static void hns3_free_buffer_detach(struct hns3_enet_ring *ring, int i)
{
	struct hns3_desc_cb *cb = &ring->desc_cb[i];

	if (!ring->desc_cb[i].dma)
		return;

	hns3_buffer_detach(ring, i);
	hns3_free_buffer(ring, cb);
}