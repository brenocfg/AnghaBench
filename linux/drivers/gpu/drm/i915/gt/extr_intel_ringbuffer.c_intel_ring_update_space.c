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
struct intel_ring {unsigned int space; int /*<<< orphan*/  size; int /*<<< orphan*/  emit; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 unsigned int __intel_ring_space (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int intel_ring_update_space(struct intel_ring *ring)
{
	unsigned int space;

	space = __intel_ring_space(ring->head, ring->emit, ring->size);

	ring->space = space;
	return space;
}