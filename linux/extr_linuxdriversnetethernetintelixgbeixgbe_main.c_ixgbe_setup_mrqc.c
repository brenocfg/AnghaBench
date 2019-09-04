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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
struct ixgbe_adapter {int hw_tcs; int flags; int flags2; int /*<<< orphan*/  num_rx_pools; TYPE_1__* ring_feature; struct ixgbe_hw hw; } ;
struct TYPE_3__ {scalar_t__ mask; } ;

/* Variables and functions */
 scalar_t__ IXGBE_82599_VMDQ_4Q_MASK ; 
 int IXGBE_FLAG2_RSS_FIELD_IPV4_UDP ; 
 int IXGBE_FLAG2_RSS_FIELD_IPV6_UDP ; 
 int IXGBE_FLAG_SRIOV_ENABLED ; 
 int /*<<< orphan*/  IXGBE_MRQC ; 
 int IXGBE_MRQC_L3L4TXSWEN ; 
 int IXGBE_MRQC_MULTIPLE_RSS ; 
 int IXGBE_MRQC_RSSEN ; 
 int IXGBE_MRQC_RSS_FIELD_IPV4 ; 
 int IXGBE_MRQC_RSS_FIELD_IPV4_TCP ; 
 int IXGBE_MRQC_RSS_FIELD_IPV4_UDP ; 
 int IXGBE_MRQC_RSS_FIELD_IPV6 ; 
 int IXGBE_MRQC_RSS_FIELD_IPV6_TCP ; 
 int IXGBE_MRQC_RSS_FIELD_IPV6_UDP ; 
 int IXGBE_MRQC_RTRSS4TCEN ; 
 int IXGBE_MRQC_RTRSS8TCEN ; 
 int IXGBE_MRQC_VMDQRSS32EN ; 
 int IXGBE_MRQC_VMDQRSS64EN ; 
 int IXGBE_MRQC_VMDQRT4TCEN ; 
 int IXGBE_MRQC_VMDQRT8TCEN ; 
 int /*<<< orphan*/  IXGBE_PFVFMRQC (int /*<<< orphan*/ ) ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RXCSUM ; 
 int IXGBE_RXCSUM_PCSD ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 size_t RING_F_RSS ; 
 size_t RING_F_VMDQ ; 
 int /*<<< orphan*/  VMDQ_P (int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_mac_82598EB ; 
 scalar_t__ ixgbe_mac_X550 ; 
 int /*<<< orphan*/  ixgbe_setup_reta (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_setup_vfreta (struct ixgbe_adapter*) ; 

__attribute__((used)) static void ixgbe_setup_mrqc(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 mrqc = 0, rss_field = 0, vfmrqc = 0;
	u32 rxcsum;

	/* Disable indicating checksum in descriptor, enables RSS hash */
	rxcsum = IXGBE_READ_REG(hw, IXGBE_RXCSUM);
	rxcsum |= IXGBE_RXCSUM_PCSD;
	IXGBE_WRITE_REG(hw, IXGBE_RXCSUM, rxcsum);

	if (adapter->hw.mac.type == ixgbe_mac_82598EB) {
		if (adapter->ring_feature[RING_F_RSS].mask)
			mrqc = IXGBE_MRQC_RSSEN;
	} else {
		u8 tcs = adapter->hw_tcs;

		if (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) {
			if (tcs > 4)
				mrqc = IXGBE_MRQC_VMDQRT8TCEN;	/* 8 TCs */
			else if (tcs > 1)
				mrqc = IXGBE_MRQC_VMDQRT4TCEN;	/* 4 TCs */
			else if (adapter->ring_feature[RING_F_VMDQ].mask ==
				 IXGBE_82599_VMDQ_4Q_MASK)
				mrqc = IXGBE_MRQC_VMDQRSS32EN;
			else
				mrqc = IXGBE_MRQC_VMDQRSS64EN;

			/* Enable L3/L4 for Tx Switched packets only for X550,
			 * older devices do not support this feature
			 */
			if (hw->mac.type >= ixgbe_mac_X550)
				mrqc |= IXGBE_MRQC_L3L4TXSWEN;
		} else {
			if (tcs > 4)
				mrqc = IXGBE_MRQC_RTRSS8TCEN;
			else if (tcs > 1)
				mrqc = IXGBE_MRQC_RTRSS4TCEN;
			else
				mrqc = IXGBE_MRQC_RSSEN;
		}
	}

	/* Perform hash on these packet types */
	rss_field |= IXGBE_MRQC_RSS_FIELD_IPV4 |
		     IXGBE_MRQC_RSS_FIELD_IPV4_TCP |
		     IXGBE_MRQC_RSS_FIELD_IPV6 |
		     IXGBE_MRQC_RSS_FIELD_IPV6_TCP;

	if (adapter->flags2 & IXGBE_FLAG2_RSS_FIELD_IPV4_UDP)
		rss_field |= IXGBE_MRQC_RSS_FIELD_IPV4_UDP;
	if (adapter->flags2 & IXGBE_FLAG2_RSS_FIELD_IPV6_UDP)
		rss_field |= IXGBE_MRQC_RSS_FIELD_IPV6_UDP;

	if ((hw->mac.type >= ixgbe_mac_X550) &&
	    (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED)) {
		u16 pool = adapter->num_rx_pools;

		/* Enable VF RSS mode */
		mrqc |= IXGBE_MRQC_MULTIPLE_RSS;
		IXGBE_WRITE_REG(hw, IXGBE_MRQC, mrqc);

		/* Setup RSS through the VF registers */
		ixgbe_setup_vfreta(adapter);
		vfmrqc = IXGBE_MRQC_RSSEN;
		vfmrqc |= rss_field;

		while (pool--)
			IXGBE_WRITE_REG(hw,
					IXGBE_PFVFMRQC(VMDQ_P(pool)),
					vfmrqc);
	} else {
		ixgbe_setup_reta(adapter);
		mrqc |= rss_field;
		IXGBE_WRITE_REG(hw, IXGBE_MRQC, mrqc);
	}
}