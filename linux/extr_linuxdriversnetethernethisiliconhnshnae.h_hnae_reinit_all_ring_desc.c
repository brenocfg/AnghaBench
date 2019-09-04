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
struct hnae_ring {int desc_num; TYPE_2__* desc_cb; TYPE_1__* desc; } ;
struct hnae_handle {int q_num; TYPE_3__** qs; } ;
struct TYPE_6__ {struct hnae_ring rx_ring; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void hnae_reinit_all_ring_desc(struct hnae_handle *h)
{
	int i, j;
	struct hnae_ring *ring;

	for (i = 0; i < h->q_num; i++) {
		ring = &h->qs[i]->rx_ring;
		for (j = 0; j < ring->desc_num; j++)
			ring->desc[j].addr = cpu_to_le64(ring->desc_cb[j].dma);
	}

	wmb();	/* commit all data before submit */
}