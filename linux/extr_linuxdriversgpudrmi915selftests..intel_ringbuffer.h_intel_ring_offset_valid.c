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
struct intel_ring {unsigned int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (unsigned int,int) ; 

__attribute__((used)) static inline bool
intel_ring_offset_valid(const struct intel_ring *ring,
			unsigned int pos)
{
	if (pos & -ring->size) /* must be strictly within the ring */
		return false;

	if (!IS_ALIGNED(pos, 8)) /* must be qword aligned */
		return false;

	return true;
}