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
struct i40e_ring {int /*<<< orphan*/  tail; int /*<<< orphan*/  next_to_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void i40e_xdp_ring_update_tail(struct i40e_ring *xdp_ring)
{
	/* Force memory writes to complete before letting h/w
	 * know there are new descriptors to fetch.
	 */
	wmb();
	writel_relaxed(xdp_ring->next_to_use, xdp_ring->tail);
}