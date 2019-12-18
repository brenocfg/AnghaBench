#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {scalar_t__ mtu; } ;
struct iavf_hw {scalar_t__ hw_addr; } ;
struct iavf_adapter {int flags; int num_active_queues; TYPE_1__* rx_rings; struct net_device* netdev; struct iavf_hw hw; } ;
struct TYPE_3__ {unsigned int rx_buf_len; scalar_t__ tail; } ;

/* Variables and functions */
 scalar_t__ ETH_DATA_LEN ; 
 int /*<<< orphan*/  IAVF_2K_TOO_SMALL_WITH_PADDING ; 
 int IAVF_FLAG_LEGACY_RX ; 
 scalar_t__ IAVF_QRX_TAIL1 (int) ; 
 unsigned int IAVF_RXBUFFER_1536 ; 
 unsigned int IAVF_RXBUFFER_2048 ; 
 unsigned int IAVF_RXBUFFER_3072 ; 
 unsigned int NET_IP_ALIGN ; 
 int /*<<< orphan*/  clear_ring_build_skb_enabled (TYPE_1__*) ; 
 int /*<<< orphan*/  set_ring_build_skb_enabled (TYPE_1__*) ; 

__attribute__((used)) static void iavf_configure_rx(struct iavf_adapter *adapter)
{
	unsigned int rx_buf_len = IAVF_RXBUFFER_2048;
	struct iavf_hw *hw = &adapter->hw;
	int i;

	/* Legacy Rx will always default to a 2048 buffer size. */
#if (PAGE_SIZE < 8192)
	if (!(adapter->flags & IAVF_FLAG_LEGACY_RX)) {
		struct net_device *netdev = adapter->netdev;

		/* For jumbo frames on systems with 4K pages we have to use
		 * an order 1 page, so we might as well increase the size
		 * of our Rx buffer to make better use of the available space
		 */
		rx_buf_len = IAVF_RXBUFFER_3072;

		/* We use a 1536 buffer size for configurations with
		 * standard Ethernet mtu.  On x86 this gives us enough room
		 * for shared info and 192 bytes of padding.
		 */
		if (!IAVF_2K_TOO_SMALL_WITH_PADDING &&
		    (netdev->mtu <= ETH_DATA_LEN))
			rx_buf_len = IAVF_RXBUFFER_1536 - NET_IP_ALIGN;
	}
#endif

	for (i = 0; i < adapter->num_active_queues; i++) {
		adapter->rx_rings[i].tail = hw->hw_addr + IAVF_QRX_TAIL1(i);
		adapter->rx_rings[i].rx_buf_len = rx_buf_len;

		if (adapter->flags & IAVF_FLAG_LEGACY_RX)
			clear_ring_build_skb_enabled(&adapter->rx_rings[i]);
		else
			set_ring_build_skb_enabled(&adapter->rx_rings[i]);
	}
}