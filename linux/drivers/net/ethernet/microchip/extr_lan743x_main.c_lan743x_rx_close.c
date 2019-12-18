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
struct lan743x_rx {int /*<<< orphan*/  napi; int /*<<< orphan*/  channel_number; struct lan743x_adapter* adapter; } ;
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAC_CMD ; 
 int /*<<< orphan*/  DMAC_CMD_STOP_R_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMAC_INT_BIT_RXFRM_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMAC_INT_EN_CLR ; 
 int /*<<< orphan*/  FCT_RX_CTL ; 
 int /*<<< orphan*/  FCT_RX_CTL_DIS_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FCT_RX_CTL_EN_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_BIT_DMA_RX_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_EN_CLR ; 
 int /*<<< orphan*/  lan743x_csr_wait_for_bit (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_dmac_rx_wait_till_stopped (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_rx_ring_cleanup (struct lan743x_rx*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lan743x_rx_close(struct lan743x_rx *rx)
{
	struct lan743x_adapter *adapter = rx->adapter;

	lan743x_csr_write(adapter, FCT_RX_CTL,
			  FCT_RX_CTL_DIS_(rx->channel_number));
	lan743x_csr_wait_for_bit(adapter, FCT_RX_CTL,
				 FCT_RX_CTL_EN_(rx->channel_number),
				 0, 1000, 20000, 100);

	lan743x_csr_write(adapter, DMAC_CMD,
			  DMAC_CMD_STOP_R_(rx->channel_number));
	lan743x_dmac_rx_wait_till_stopped(adapter, rx->channel_number);

	lan743x_csr_write(adapter, DMAC_INT_EN_CLR,
			  DMAC_INT_BIT_RXFRM_(rx->channel_number));
	lan743x_csr_write(adapter, INT_EN_CLR,
			  INT_BIT_DMA_RX_(rx->channel_number));
	napi_disable(&rx->napi);

	netif_napi_del(&rx->napi);

	lan743x_rx_ring_cleanup(rx);
}