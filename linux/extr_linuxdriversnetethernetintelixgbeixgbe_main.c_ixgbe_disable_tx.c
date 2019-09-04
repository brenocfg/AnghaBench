#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ixgbe_ring {int /*<<< orphan*/  reg_idx; } ;
struct TYPE_2__ {int type; } ;
struct ixgbe_hw {TYPE_1__ mac; int /*<<< orphan*/  hw_addr; } ;
struct ixgbe_adapter {int num_tx_queues; int num_xdp_queues; struct ixgbe_ring** xdp_ring; struct ixgbe_ring** tx_ring; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_DMATXCTL ; 
 int IXGBE_DMATXCTL_TE ; 
 int /*<<< orphan*/  IXGBE_LINKS ; 
 int IXGBE_LINKS_UP ; 
 int IXGBE_MAX_RX_DESC_POLL ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_TXDCTL (int /*<<< orphan*/ ) ; 
 int IXGBE_TXDCTL_ENABLE ; 
 int IXGBE_TXDCTL_SWFLSH ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*) ; 
 int ixgbe_get_completion_timeout (struct ixgbe_adapter*) ; 
#define  ixgbe_mac_82599EB 132 
#define  ixgbe_mac_X540 131 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_x 129 
#define  ixgbe_mac_x550em_a 128 
 scalar_t__ ixgbe_removed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (unsigned long,unsigned long) ; 

void ixgbe_disable_tx(struct ixgbe_adapter *adapter)
{
	unsigned long wait_delay, delay_interval;
	struct ixgbe_hw *hw = &adapter->hw;
	int i, wait_loop;
	u32 txdctl;

	if (ixgbe_removed(hw->hw_addr))
		return;

	/* disable all enabled Tx queues */
	for (i = 0; i < adapter->num_tx_queues; i++) {
		struct ixgbe_ring *ring = adapter->tx_ring[i];
		u8 reg_idx = ring->reg_idx;

		IXGBE_WRITE_REG(hw, IXGBE_TXDCTL(reg_idx), IXGBE_TXDCTL_SWFLSH);
	}

	/* disable all enabled XDP Tx queues */
	for (i = 0; i < adapter->num_xdp_queues; i++) {
		struct ixgbe_ring *ring = adapter->xdp_ring[i];
		u8 reg_idx = ring->reg_idx;

		IXGBE_WRITE_REG(hw, IXGBE_TXDCTL(reg_idx), IXGBE_TXDCTL_SWFLSH);
	}

	/* If the link is not up there shouldn't be much in the way of
	 * pending transactions. Those that are left will be flushed out
	 * when the reset logic goes through the flush sequence to clean out
	 * the pending Tx transactions.
	 */
	if (!(IXGBE_READ_REG(hw, IXGBE_LINKS) & IXGBE_LINKS_UP))
		goto dma_engine_disable;

	/* Determine our minimum delay interval. We will increase this value
	 * with each subsequent test. This way if the device returns quickly
	 * we should spend as little time as possible waiting, however as
	 * the time increases we will wait for larger periods of time.
	 *
	 * The trick here is that we increase the interval using the
	 * following pattern: 1x 3x 5x 7x 9x 11x 13x 15x 17x 19x. The result
	 * of that wait is that it totals up to 100x whatever interval we
	 * choose. Since our minimum wait is 100us we can just divide the
	 * total timeout by 100 to get our minimum delay interval.
	 */
	delay_interval = ixgbe_get_completion_timeout(adapter) / 100;

	wait_loop = IXGBE_MAX_RX_DESC_POLL;
	wait_delay = delay_interval;

	while (wait_loop--) {
		usleep_range(wait_delay, wait_delay + 10);
		wait_delay += delay_interval * 2;
		txdctl = 0;

		/* OR together the reading of all the active TXDCTL registers,
		 * and then test the result. We need the disable to complete
		 * before we start freeing the memory and invalidating the
		 * DMA mappings.
		 */
		for (i = 0; i < adapter->num_tx_queues; i++) {
			struct ixgbe_ring *ring = adapter->tx_ring[i];
			u8 reg_idx = ring->reg_idx;

			txdctl |= IXGBE_READ_REG(hw, IXGBE_TXDCTL(reg_idx));
		}
		for (i = 0; i < adapter->num_xdp_queues; i++) {
			struct ixgbe_ring *ring = adapter->xdp_ring[i];
			u8 reg_idx = ring->reg_idx;

			txdctl |= IXGBE_READ_REG(hw, IXGBE_TXDCTL(reg_idx));
		}

		if (!(txdctl & IXGBE_TXDCTL_ENABLE))
			goto dma_engine_disable;
	}

	e_err(drv,
	      "TXDCTL.ENABLE for one or more queues not cleared within the polling period\n");

dma_engine_disable:
	/* Disable the Tx DMA engine on 82599 and later MAC */
	switch (hw->mac.type) {
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		IXGBE_WRITE_REG(hw, IXGBE_DMATXCTL,
				(IXGBE_READ_REG(hw, IXGBE_DMATXCTL) &
				 ~IXGBE_DMATXCTL_TE));
		/* fall through */
	default:
		break;
	}
}