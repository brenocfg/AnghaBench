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
struct ixgbe_ring_container {scalar_t__ next_update; int /*<<< orphan*/  count; struct ixgbe_ring* ring; } ;
struct ixgbe_ring {struct ixgbe_ring* next; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 

__attribute__((used)) static void ixgbe_add_ring(struct ixgbe_ring *ring,
			   struct ixgbe_ring_container *head)
{
	ring->next = head->ring;
	head->ring = ring;
	head->count++;
	head->next_update = jiffies + 1;
}