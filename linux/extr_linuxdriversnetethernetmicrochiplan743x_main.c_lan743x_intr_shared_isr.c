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
struct lan743x_adapter {int /*<<< orphan*/ * tx; int /*<<< orphan*/ * rx; } ;

/* Variables and functions */
 int INT_BIT_1588_ ; 
 int INT_BIT_ALL_OTHER_ ; 
 int INT_BIT_ALL_RX_ ; 
 int INT_BIT_ALL_TX_ ; 
 int INT_BIT_DMA_RX_ (unsigned int) ; 
 int INT_BIT_DMA_TX_ (unsigned int) ; 
 int INT_BIT_SW_GP_ ; 
 int /*<<< orphan*/  INT_EN_CLR ; 
 unsigned int LAN743X_USED_RX_CHANNELS ; 
 unsigned int LAN743X_USED_TX_CHANNELS ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lan743x_intr_software_isr (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_ptp_isr (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_rx_isr (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lan743x_tx_isr (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void lan743x_intr_shared_isr(void *context, u32 int_sts, u32 flags)
{
	struct lan743x_adapter *adapter = context;
	unsigned int channel;

	if (int_sts & INT_BIT_ALL_RX_) {
		for (channel = 0; channel < LAN743X_USED_RX_CHANNELS;
			channel++) {
			u32 int_bit = INT_BIT_DMA_RX_(channel);

			if (int_sts & int_bit) {
				lan743x_rx_isr(&adapter->rx[channel],
					       int_bit, flags);
				int_sts &= ~int_bit;
			}
		}
	}
	if (int_sts & INT_BIT_ALL_TX_) {
		for (channel = 0; channel < LAN743X_USED_TX_CHANNELS;
			channel++) {
			u32 int_bit = INT_BIT_DMA_TX_(channel);

			if (int_sts & int_bit) {
				lan743x_tx_isr(&adapter->tx[channel],
					       int_bit, flags);
				int_sts &= ~int_bit;
			}
		}
	}
	if (int_sts & INT_BIT_ALL_OTHER_) {
		if (int_sts & INT_BIT_SW_GP_) {
			lan743x_intr_software_isr(adapter);
			int_sts &= ~INT_BIT_SW_GP_;
		}
		if (int_sts & INT_BIT_1588_) {
			lan743x_ptp_isr(adapter);
			int_sts &= ~INT_BIT_1588_;
		}
	}
	if (int_sts)
		lan743x_csr_write(adapter, INT_EN_CLR, int_sts);
}