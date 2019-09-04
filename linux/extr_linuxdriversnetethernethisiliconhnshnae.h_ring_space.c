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
struct hnae_ring {int desc_num; int /*<<< orphan*/  next_to_use; int /*<<< orphan*/  next_to_clean; } ;

/* Variables and functions */
 int ring_dist (struct hnae_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ring_space(struct hnae_ring *ring)
{
	return ring->desc_num -
		ring_dist(ring, ring->next_to_clean, ring->next_to_use) - 1;
}