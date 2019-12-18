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
typedef  int u32 ;
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {int rss_queues; int vfs_allocated_count; int rss_indir_tbl_init; int* rss_indir_tbl; int flags; struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  rss_key ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_MRQC ; 
 int E1000_MRQC_ENABLE_RSS_MQ ; 
 int E1000_MRQC_ENABLE_VMDQ ; 
 int E1000_MRQC_ENABLE_VMDQ_RSS_MQ ; 
 int E1000_MRQC_RSS_FIELD_IPV4 ; 
 int E1000_MRQC_RSS_FIELD_IPV4_TCP ; 
 int E1000_MRQC_RSS_FIELD_IPV4_UDP ; 
 int E1000_MRQC_RSS_FIELD_IPV6 ; 
 int E1000_MRQC_RSS_FIELD_IPV6_TCP ; 
 int E1000_MRQC_RSS_FIELD_IPV6_TCP_EX ; 
 int E1000_MRQC_RSS_FIELD_IPV6_UDP ; 
 int /*<<< orphan*/  E1000_RSSRK (int) ; 
 int /*<<< orphan*/  E1000_RXCSUM ; 
 int E1000_RXCSUM_CRCOFL ; 
 int E1000_RXCSUM_PCSD ; 
 int /*<<< orphan*/  E1000_VT_CTL ; 
 int E1000_VT_CTL_DEFAULT_POOL_MASK ; 
 int E1000_VT_CTL_DEFAULT_POOL_SHIFT ; 
 int E1000_VT_CTL_DISABLE_DEF_POOL ; 
 int IGB_FLAG_RSS_FIELD_IPV4_UDP ; 
 int IGB_FLAG_RSS_FIELD_IPV6_UDP ; 
 int IGB_RETA_SIZE ; 
 int e1000_82575 ; 
#define  e1000_82576 128 
 int e1000_i211 ; 
 int /*<<< orphan*/  igb_vmm_control (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_write_rss_indir_tbl (struct igb_adapter*) ; 
 int /*<<< orphan*/  netdev_rss_key_fill (int*,int) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void igb_setup_mrqc(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 mrqc, rxcsum;
	u32 j, num_rx_queues;
	u32 rss_key[10];

	netdev_rss_key_fill(rss_key, sizeof(rss_key));
	for (j = 0; j < 10; j++)
		wr32(E1000_RSSRK(j), rss_key[j]);

	num_rx_queues = adapter->rss_queues;

	switch (hw->mac.type) {
	case e1000_82576:
		/* 82576 supports 2 RSS queues for SR-IOV */
		if (adapter->vfs_allocated_count)
			num_rx_queues = 2;
		break;
	default:
		break;
	}

	if (adapter->rss_indir_tbl_init != num_rx_queues) {
		for (j = 0; j < IGB_RETA_SIZE; j++)
			adapter->rss_indir_tbl[j] =
			(j * num_rx_queues) / IGB_RETA_SIZE;
		adapter->rss_indir_tbl_init = num_rx_queues;
	}
	igb_write_rss_indir_tbl(adapter);

	/* Disable raw packet checksumming so that RSS hash is placed in
	 * descriptor on writeback.  No need to enable TCP/UDP/IP checksum
	 * offloads as they are enabled by default
	 */
	rxcsum = rd32(E1000_RXCSUM);
	rxcsum |= E1000_RXCSUM_PCSD;

	if (adapter->hw.mac.type >= e1000_82576)
		/* Enable Receive Checksum Offload for SCTP */
		rxcsum |= E1000_RXCSUM_CRCOFL;

	/* Don't need to set TUOFL or IPOFL, they default to 1 */
	wr32(E1000_RXCSUM, rxcsum);

	/* Generate RSS hash based on packet types, TCP/UDP
	 * port numbers and/or IPv4/v6 src and dst addresses
	 */
	mrqc = E1000_MRQC_RSS_FIELD_IPV4 |
	       E1000_MRQC_RSS_FIELD_IPV4_TCP |
	       E1000_MRQC_RSS_FIELD_IPV6 |
	       E1000_MRQC_RSS_FIELD_IPV6_TCP |
	       E1000_MRQC_RSS_FIELD_IPV6_TCP_EX;

	if (adapter->flags & IGB_FLAG_RSS_FIELD_IPV4_UDP)
		mrqc |= E1000_MRQC_RSS_FIELD_IPV4_UDP;
	if (adapter->flags & IGB_FLAG_RSS_FIELD_IPV6_UDP)
		mrqc |= E1000_MRQC_RSS_FIELD_IPV6_UDP;

	/* If VMDq is enabled then we set the appropriate mode for that, else
	 * we default to RSS so that an RSS hash is calculated per packet even
	 * if we are only using one queue
	 */
	if (adapter->vfs_allocated_count) {
		if (hw->mac.type > e1000_82575) {
			/* Set the default pool for the PF's first queue */
			u32 vtctl = rd32(E1000_VT_CTL);

			vtctl &= ~(E1000_VT_CTL_DEFAULT_POOL_MASK |
				   E1000_VT_CTL_DISABLE_DEF_POOL);
			vtctl |= adapter->vfs_allocated_count <<
				E1000_VT_CTL_DEFAULT_POOL_SHIFT;
			wr32(E1000_VT_CTL, vtctl);
		}
		if (adapter->rss_queues > 1)
			mrqc |= E1000_MRQC_ENABLE_VMDQ_RSS_MQ;
		else
			mrqc |= E1000_MRQC_ENABLE_VMDQ;
	} else {
		if (hw->mac.type != e1000_i211)
			mrqc |= E1000_MRQC_ENABLE_RSS_MQ;
	}
	igb_vmm_control(adapter);

	wr32(E1000_MRQC, mrqc);
}