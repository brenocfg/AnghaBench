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
struct ixgbevf_ring_container {int /*<<< orphan*/  count; struct ixgbevf_ring* ring; } ;
struct ixgbevf_ring {struct ixgbevf_ring* next; } ;

/* Variables and functions */

__attribute__((used)) static void ixgbevf_add_ring(struct ixgbevf_ring *ring,
			     struct ixgbevf_ring_container *head)
{
	ring->next = head->ring;
	head->ring = ring;
	head->count++;
}