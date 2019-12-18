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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct e1000_ring {int count; struct e1000_buffer* buffer_info; } ;
struct e1000_hw {int dummy; } ;
struct e1000_buffer {int /*<<< orphan*/  skb; int /*<<< orphan*/  dma; int /*<<< orphan*/  length; } ;
struct e1000_adapter {struct e1000_hw hw; struct pci_dev* pdev; struct e1000_ring test_rx_ring; struct e1000_ring test_tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  RDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int e1000_check_lbtest_frame (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e1000_create_lbtest_frame (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int e1000_run_loopback_test(struct e1000_adapter *adapter)
{
	struct e1000_ring *tx_ring = &adapter->test_tx_ring;
	struct e1000_ring *rx_ring = &adapter->test_rx_ring;
	struct pci_dev *pdev = adapter->pdev;
	struct e1000_hw *hw = &adapter->hw;
	struct e1000_buffer *buffer_info;
	int i, j, k, l;
	int lc;
	int good_cnt;
	int ret_val = 0;
	unsigned long time;

	ew32(RDT(0), rx_ring->count - 1);

	/* Calculate the loop count based on the largest descriptor ring
	 * The idea is to wrap the largest ring a number of times using 64
	 * send/receive pairs during each loop
	 */

	if (rx_ring->count <= tx_ring->count)
		lc = ((tx_ring->count / 64) * 2) + 1;
	else
		lc = ((rx_ring->count / 64) * 2) + 1;

	k = 0;
	l = 0;
	/* loop count loop */
	for (j = 0; j <= lc; j++) {
		/* send the packets */
		for (i = 0; i < 64; i++) {
			buffer_info = &tx_ring->buffer_info[k];

			e1000_create_lbtest_frame(buffer_info->skb, 1024);
			dma_sync_single_for_device(&pdev->dev,
						   buffer_info->dma,
						   buffer_info->length,
						   DMA_TO_DEVICE);
			k++;
			if (k == tx_ring->count)
				k = 0;
		}
		ew32(TDT(0), k);
		e1e_flush();
		msleep(200);
		time = jiffies;	/* set the start time for the receive */
		good_cnt = 0;
		/* receive the sent packets */
		do {
			buffer_info = &rx_ring->buffer_info[l];

			dma_sync_single_for_cpu(&pdev->dev,
						buffer_info->dma, 2048,
						DMA_FROM_DEVICE);

			ret_val = e1000_check_lbtest_frame(buffer_info->skb,
							   1024);
			if (!ret_val)
				good_cnt++;
			l++;
			if (l == rx_ring->count)
				l = 0;
			/* time + 20 msecs (200 msecs on 2.4) is more than
			 * enough time to complete the receives, if it's
			 * exceeded, break and error off
			 */
		} while ((good_cnt < 64) && !time_after(jiffies, time + 20));
		if (good_cnt != 64) {
			ret_val = 13;	/* ret_val is the same as mis-compare */
			break;
		}
		if (time_after(jiffies, time + 20)) {
			ret_val = 14;	/* error code for time out error */
			break;
		}
	}
	return ret_val;
}