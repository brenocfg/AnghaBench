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
struct net_device {int mtu; } ;
struct igbvf_adapter {int max_frame_size; int rx_buffer_len; int /*<<< orphan*/  state; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETH_FCS_LEN ; 
 int ETH_FRAME_LEN ; 
 int ETH_HLEN ; 
 int PAGE_SIZE ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  __IGBVF_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  igbvf_down (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  igbvf_reset (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  igbvf_up (struct igbvf_adapter*) ; 
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int igbvf_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct igbvf_adapter *adapter = netdev_priv(netdev);
	int max_frame = new_mtu + ETH_HLEN + ETH_FCS_LEN;

	while (test_and_set_bit(__IGBVF_RESETTING, &adapter->state))
		usleep_range(1000, 2000);
	/* igbvf_down has a dependency on max_frame_size */
	adapter->max_frame_size = max_frame;
	if (netif_running(netdev))
		igbvf_down(adapter);

	/* NOTE: netdev_alloc_skb reserves 16 bytes, and typically NET_IP_ALIGN
	 * means we reserve 2 more, this pushes us to allocate from the next
	 * larger slab size.
	 * i.e. RXBUFFER_2048 --> size-4096 slab
	 * However with the new *_jumbo_rx* routines, jumbo receives will use
	 * fragmented skbs
	 */

	if (max_frame <= 1024)
		adapter->rx_buffer_len = 1024;
	else if (max_frame <= 2048)
		adapter->rx_buffer_len = 2048;
	else
#if (PAGE_SIZE / 2) > 16384
		adapter->rx_buffer_len = 16384;
#else
		adapter->rx_buffer_len = PAGE_SIZE / 2;
#endif

	/* adjust allocation if LPE protects us, and we aren't using SBP */
	if ((max_frame == ETH_FRAME_LEN + ETH_FCS_LEN) ||
	    (max_frame == ETH_FRAME_LEN + VLAN_HLEN + ETH_FCS_LEN))
		adapter->rx_buffer_len = ETH_FRAME_LEN + VLAN_HLEN +
					 ETH_FCS_LEN;

	dev_info(&adapter->pdev->dev, "changing MTU from %d to %d\n",
		 netdev->mtu, new_mtu);
	netdev->mtu = new_mtu;

	if (netif_running(netdev))
		igbvf_up(adapter);
	else
		igbvf_reset(adapter);

	clear_bit(__IGBVF_RESETTING, &adapter->state);

	return 0;
}