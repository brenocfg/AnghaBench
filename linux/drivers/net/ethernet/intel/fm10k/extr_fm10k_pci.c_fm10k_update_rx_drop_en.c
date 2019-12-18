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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct fm10k_ring {int reg_idx; int /*<<< orphan*/  qos_pc; } ;
struct fm10k_hw {int dummy; } ;
struct fm10k_intfc {int rx_pause; int pfc_en; int num_rx_queues; struct fm10k_ring** rx_ring; struct fm10k_hw hw; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM10K_RXDCTL (int) ; 
 int /*<<< orphan*/  FM10K_RXDCTL_DROP_ON_EMPTY ; 
 int /*<<< orphan*/  FM10K_RXDCTL_WRITE_BACK_MIN_DELAY ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fm10k_update_rx_drop_en(struct fm10k_intfc *interface)
{
	struct fm10k_hw *hw = &interface->hw;
	u8 rx_pause = interface->rx_pause;
	int i;

#ifdef CONFIG_DCB
	if (interface->pfc_en)
		rx_pause = interface->pfc_en;

#endif
	for (i = 0; i < interface->num_rx_queues; i++) {
		struct fm10k_ring *ring = interface->rx_ring[i];
		u32 rxdctl = FM10K_RXDCTL_WRITE_BACK_MIN_DELAY;
		u8 reg_idx = ring->reg_idx;

		if (!(rx_pause & BIT(ring->qos_pc)))
			rxdctl |= FM10K_RXDCTL_DROP_ON_EMPTY;

		fm10k_write_reg(hw, FM10K_RXDCTL(reg_idx), rxdctl);
	}
}