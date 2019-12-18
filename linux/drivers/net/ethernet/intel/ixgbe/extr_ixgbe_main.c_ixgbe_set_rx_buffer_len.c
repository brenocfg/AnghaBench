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
struct net_device {int mtu; } ;
struct ixgbe_ring {int /*<<< orphan*/  state; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {int flags; int num_rx_queues; int flags2; struct ixgbe_ring** rx_ring; struct net_device* netdev; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int ETH_FCS_LEN ; 
 int ETH_FRAME_LEN ; 
 int ETH_HLEN ; 
 scalar_t__ IXGBE_2K_TOO_SMALL_WITH_PADDING ; 
 int IXGBE_FCOE_JUMBO_FRAME_SIZE ; 
 int IXGBE_FLAG2_RSC_ENABLED ; 
 int IXGBE_FLAG2_RX_LEGACY ; 
 int IXGBE_FLAG_FCOE_ENABLED ; 
 int /*<<< orphan*/  IXGBE_HLREG0 ; 
 int IXGBE_HLREG0_JUMBOEN ; 
 int /*<<< orphan*/  IXGBE_MHADD ; 
 int IXGBE_MHADD_MFS_MASK ; 
 int IXGBE_MHADD_MFS_SHIFT ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __IXGBE_RX_3K_BUFFER ; 
 int /*<<< orphan*/  __IXGBE_RX_BUILD_SKB_ENABLED ; 
 int /*<<< orphan*/  __IXGBE_RX_FCOE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_ring_rsc_enabled (struct ixgbe_ring*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_ring_rsc_enabled (struct ixgbe_ring*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbe_set_rx_buffer_len(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	int max_frame = netdev->mtu + ETH_HLEN + ETH_FCS_LEN;
	struct ixgbe_ring *rx_ring;
	int i;
	u32 mhadd, hlreg0;

#ifdef IXGBE_FCOE
	/* adjust max frame to be able to do baby jumbo for FCoE */
	if ((adapter->flags & IXGBE_FLAG_FCOE_ENABLED) &&
	    (max_frame < IXGBE_FCOE_JUMBO_FRAME_SIZE))
		max_frame = IXGBE_FCOE_JUMBO_FRAME_SIZE;

#endif /* IXGBE_FCOE */

	/* adjust max frame to be at least the size of a standard frame */
	if (max_frame < (ETH_FRAME_LEN + ETH_FCS_LEN))
		max_frame = (ETH_FRAME_LEN + ETH_FCS_LEN);

	mhadd = IXGBE_READ_REG(hw, IXGBE_MHADD);
	if (max_frame != (mhadd >> IXGBE_MHADD_MFS_SHIFT)) {
		mhadd &= ~IXGBE_MHADD_MFS_MASK;
		mhadd |= max_frame << IXGBE_MHADD_MFS_SHIFT;

		IXGBE_WRITE_REG(hw, IXGBE_MHADD, mhadd);
	}

	hlreg0 = IXGBE_READ_REG(hw, IXGBE_HLREG0);
	/* set jumbo enable since MHADD.MFS is keeping size locked at max_frame */
	hlreg0 |= IXGBE_HLREG0_JUMBOEN;
	IXGBE_WRITE_REG(hw, IXGBE_HLREG0, hlreg0);

	/*
	 * Setup the HW Rx Head and Tail Descriptor Pointers and
	 * the Base and Length of the Rx Descriptor Ring
	 */
	for (i = 0; i < adapter->num_rx_queues; i++) {
		rx_ring = adapter->rx_ring[i];

		clear_ring_rsc_enabled(rx_ring);
		clear_bit(__IXGBE_RX_3K_BUFFER, &rx_ring->state);
		clear_bit(__IXGBE_RX_BUILD_SKB_ENABLED, &rx_ring->state);

		if (adapter->flags2 & IXGBE_FLAG2_RSC_ENABLED)
			set_ring_rsc_enabled(rx_ring);

		if (test_bit(__IXGBE_RX_FCOE, &rx_ring->state))
			set_bit(__IXGBE_RX_3K_BUFFER, &rx_ring->state);

		if (adapter->flags2 & IXGBE_FLAG2_RX_LEGACY)
			continue;

		set_bit(__IXGBE_RX_BUILD_SKB_ENABLED, &rx_ring->state);

#if (PAGE_SIZE < 8192)
		if (adapter->flags2 & IXGBE_FLAG2_RSC_ENABLED)
			set_bit(__IXGBE_RX_3K_BUFFER, &rx_ring->state);

		if (IXGBE_2K_TOO_SMALL_WITH_PADDING ||
		    (max_frame > (ETH_FRAME_LEN + ETH_FCS_LEN)))
			set_bit(__IXGBE_RX_3K_BUFFER, &rx_ring->state);
#endif
	}
}