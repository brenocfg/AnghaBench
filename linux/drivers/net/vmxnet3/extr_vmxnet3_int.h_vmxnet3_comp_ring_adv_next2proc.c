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
struct vmxnet3_comp_ring {scalar_t__ next2proc; scalar_t__ size; int /*<<< orphan*/  gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_FLIP_RING_GEN (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void
vmxnet3_comp_ring_adv_next2proc(struct vmxnet3_comp_ring *ring)
{
	ring->next2proc++;
	if (unlikely(ring->next2proc == ring->size)) {
		ring->next2proc = 0;
		VMXNET3_FLIP_RING_GEN(ring->gen);
	}
}