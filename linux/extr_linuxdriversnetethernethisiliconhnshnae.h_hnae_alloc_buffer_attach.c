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
struct hnae_ring {TYPE_2__* desc_cb; TYPE_1__* desc; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int hnae_reserve_buffer_map (struct hnae_ring*,TYPE_2__*) ; 

__attribute__((used)) static inline int hnae_alloc_buffer_attach(struct hnae_ring *ring, int i)
{
	int ret = hnae_reserve_buffer_map(ring, &ring->desc_cb[i]);

	if (ret)
		return ret;

	ring->desc[i].addr = cpu_to_le64(ring->desc_cb[i].dma);

	return 0;
}