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
struct hnae_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  next_to_use ; 
 int /*<<< orphan*/  ring_ptr_move_bw (struct hnae_ring*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unfill_desc(struct hnae_ring *ring)
{
	ring_ptr_move_bw(ring, next_to_use);
}