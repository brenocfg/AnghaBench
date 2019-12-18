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
typedef  int u32 ;
typedef  int u16 ;
struct ice_ring {int next_to_use; int next_to_alloc; int /*<<< orphan*/  tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_release_rx_desc(struct ice_ring *rx_ring, u32 val)
{
	u16 prev_ntu = rx_ring->next_to_use;

	rx_ring->next_to_use = val;

	/* update next to alloc since we have filled the ring */
	rx_ring->next_to_alloc = val;

	/* QRX_TAIL will be updated with any tail value, but hardware ignores
	 * the lower 3 bits. This makes it so we only bump tail on meaningful
	 * boundaries. Also, this allows us to bump tail on intervals of 8 up to
	 * the budget depending on the current traffic load.
	 */
	val &= ~0x7;
	if (prev_ntu != val) {
		/* Force memory writes to complete before letting h/w
		 * know there are new descriptors to fetch. (Only
		 * applicable for weak-ordered memory model archs,
		 * such as IA-64).
		 */
		wmb();
		writel(val, rx_ring->tail);
	}
}