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
struct vmxnet3_cmd_ring {int /*<<< orphan*/  size; int /*<<< orphan*/  next2comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_INC_RING_IDX_ONLY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
vmxnet3_cmd_ring_adv_next2comp(struct vmxnet3_cmd_ring *ring)
{
	VMXNET3_INC_RING_IDX_ONLY(ring->next2comp, ring->size);
}