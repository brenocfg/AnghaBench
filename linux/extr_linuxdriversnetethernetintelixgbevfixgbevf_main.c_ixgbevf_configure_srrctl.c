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
struct ixgbevf_ring {int dummy; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbevf_adapter {struct ixgbe_hw hw; } ;

/* Variables and functions */
 int IXGBEVF_RXBUFFER_2048 ; 
 int IXGBEVF_RXBUFFER_3072 ; 
 int IXGBEVF_RX_HDR_SIZE ; 
 int IXGBE_SRRCTL_BSIZEHDRSIZE_SHIFT ; 
 int IXGBE_SRRCTL_BSIZEPKT_SHIFT ; 
 int IXGBE_SRRCTL_DESCTYPE_ADV_ONEBUF ; 
 int IXGBE_SRRCTL_DROP_EN ; 
 int /*<<< orphan*/  IXGBE_VFSRRCTL (int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ring_uses_large_buffer (struct ixgbevf_ring*) ; 

__attribute__((used)) static void ixgbevf_configure_srrctl(struct ixgbevf_adapter *adapter,
				     struct ixgbevf_ring *ring, int index)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 srrctl;

	srrctl = IXGBE_SRRCTL_DROP_EN;

	srrctl |= IXGBEVF_RX_HDR_SIZE << IXGBE_SRRCTL_BSIZEHDRSIZE_SHIFT;
	if (ring_uses_large_buffer(ring))
		srrctl |= IXGBEVF_RXBUFFER_3072 >> IXGBE_SRRCTL_BSIZEPKT_SHIFT;
	else
		srrctl |= IXGBEVF_RXBUFFER_2048 >> IXGBE_SRRCTL_BSIZEPKT_SHIFT;
	srrctl |= IXGBE_SRRCTL_DESCTYPE_ADV_ONEBUF;

	IXGBE_WRITE_REG(hw, IXGBE_VFSRRCTL(index), srrctl);
}