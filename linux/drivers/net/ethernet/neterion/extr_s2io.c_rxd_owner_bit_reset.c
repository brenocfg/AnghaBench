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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct mac_info {struct ring_info* rings; } ;
struct config_param {int rx_ring_num; struct rx_ring_config* rx_cfg; } ;
struct s2io_nic {size_t rxd_mode; struct net_device* dev; struct mac_info mac_control; struct config_param config; } ;
struct rx_ring_config {int num_rxd; } ;
struct ring_info {struct buffAdd** ba; TYPE_2__* rx_blocks; } ;
struct net_device {int mtu; } ;
struct buffAdd {int dummy; } ;
struct RxD_t {int /*<<< orphan*/  Control_1; } ;
struct TYPE_4__ {TYPE_1__* rxds; } ;
struct TYPE_3__ {struct RxD_t* virt_addr; } ;

/* Variables and functions */
 int ALIGN_SIZE ; 
 int BUF0_LEN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int HEADER_802_2_SIZE ; 
 int HEADER_ETHERNET_II_802_3_SIZE ; 
 int HEADER_SNAP_SIZE ; 
 scalar_t__ NET_IP_ALIGN ; 
 size_t RXD_MODE_1 ; 
 size_t RXD_MODE_3B ; 
 int /*<<< orphan*/  RXD_OWN_XENA ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int* rxd_count ; 
 int /*<<< orphan*/  set_rxd_buffer_pointer (struct s2io_nic*,struct RxD_t*,struct buffAdd*,struct sk_buff**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_rxd_buffer_size (struct s2io_nic*,struct RxD_t*,int) ; 

__attribute__((used)) static  int rxd_owner_bit_reset(struct s2io_nic *sp)
{
	int i, j, k, blk_cnt = 0, size;
	struct config_param *config = &sp->config;
	struct mac_info *mac_control = &sp->mac_control;
	struct net_device *dev = sp->dev;
	struct RxD_t *rxdp = NULL;
	struct sk_buff *skb = NULL;
	struct buffAdd *ba = NULL;
	u64 temp0_64 = 0, temp1_64 = 0, temp2_64 = 0;

	/* Calculate the size based on ring mode */
	size = dev->mtu + HEADER_ETHERNET_II_802_3_SIZE +
		HEADER_802_2_SIZE + HEADER_SNAP_SIZE;
	if (sp->rxd_mode == RXD_MODE_1)
		size += NET_IP_ALIGN;
	else if (sp->rxd_mode == RXD_MODE_3B)
		size = dev->mtu + ALIGN_SIZE + BUF0_LEN + 4;

	for (i = 0; i < config->rx_ring_num; i++) {
		struct rx_ring_config *rx_cfg = &config->rx_cfg[i];
		struct ring_info *ring = &mac_control->rings[i];

		blk_cnt = rx_cfg->num_rxd / (rxd_count[sp->rxd_mode] + 1);

		for (j = 0; j < blk_cnt; j++) {
			for (k = 0; k < rxd_count[sp->rxd_mode]; k++) {
				rxdp = ring->rx_blocks[j].rxds[k].virt_addr;
				if (sp->rxd_mode == RXD_MODE_3B)
					ba = &ring->ba[j][k];
				if (set_rxd_buffer_pointer(sp, rxdp, ba, &skb,
							   &temp0_64,
							   &temp1_64,
							   &temp2_64,
							   size) == -ENOMEM) {
					return 0;
				}

				set_rxd_buffer_size(sp, rxdp, size);
				dma_wmb();
				/* flip the Ownership bit to Hardware */
				rxdp->Control_1 |= RXD_OWN_XENA;
			}
		}
	}
	return 0;

}