#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {int /*<<< orphan*/  num_rx_pools; TYPE_2__* ring_feature; struct ixgbe_hw hw; } ;
struct TYPE_4__ {int indices; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_PSRTYPE (int /*<<< orphan*/ ) ; 
 unsigned int IXGBE_PSRTYPE_IPV4HDR ; 
 unsigned int IXGBE_PSRTYPE_IPV6HDR ; 
 unsigned int IXGBE_PSRTYPE_L2HDR ; 
 unsigned int IXGBE_PSRTYPE_TCPHDR ; 
 unsigned int IXGBE_PSRTYPE_UDPHDR ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,unsigned int) ; 
 size_t RING_F_RSS ; 
 int /*<<< orphan*/  VMDQ_P (int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_mac_82598EB ; 

__attribute__((used)) static void ixgbe_setup_psrtype(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	int rss_i = adapter->ring_feature[RING_F_RSS].indices;
	u16 pool = adapter->num_rx_pools;

	/* PSRTYPE must be initialized in non 82598 adapters */
	u32 psrtype = IXGBE_PSRTYPE_TCPHDR |
		      IXGBE_PSRTYPE_UDPHDR |
		      IXGBE_PSRTYPE_IPV4HDR |
		      IXGBE_PSRTYPE_L2HDR |
		      IXGBE_PSRTYPE_IPV6HDR;

	if (hw->mac.type == ixgbe_mac_82598EB)
		return;

	if (rss_i > 3)
		psrtype |= 2u << 29;
	else if (rss_i > 1)
		psrtype |= 1u << 29;

	while (pool--)
		IXGBE_WRITE_REG(hw, IXGBE_PSRTYPE(VMDQ_P(pool)), psrtype);
}