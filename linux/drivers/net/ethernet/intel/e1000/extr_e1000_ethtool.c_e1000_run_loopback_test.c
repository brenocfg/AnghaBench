#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct e1000_tx_ring {int count; TYPE_1__* buffer_info; } ;
struct e1000_rx_ring {int count; TYPE_3__* buffer_info; } ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {struct pci_dev* pdev; struct e1000_rx_ring test_rx_ring; struct e1000_tx_ring test_tx_ring; struct e1000_hw hw; } ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_6__ {TYPE_2__ rxbuf; int /*<<< orphan*/  dma; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  dma; int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  E1000_RXBUFFER_2048 ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 scalar_t__ NET_IP_ALIGN ; 
 scalar_t__ NET_SKB_PAD ; 
 int /*<<< orphan*/  RDT ; 
 int /*<<< orphan*/  TDT ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int e1000_check_lbtest_frame (scalar_t__,int) ; 
 int /*<<< orphan*/  e1000_create_lbtest_frame (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int e1000_run_loopback_test(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct e1000_tx_ring *txdr = &adapter->test_tx_ring;
	struct e1000_rx_ring *rxdr = &adapter->test_rx_ring;
	struct pci_dev *pdev = adapter->pdev;
	int i, j, k, l, lc, good_cnt, ret_val = 0;
	unsigned long time;

	ew32(RDT, rxdr->count - 1);

	/* Calculate the loop count based on the largest descriptor ring
	 * The idea is to wrap the largest ring a number of times using 64
	 * send/receive pairs during each loop
	 */

	if (rxdr->count <= txdr->count)
		lc = ((txdr->count / 64) * 2) + 1;
	else
		lc = ((rxdr->count / 64) * 2) + 1;

	k = l = 0;
	for (j = 0; j <= lc; j++) { /* loop count loop */
		for (i = 0; i < 64; i++) { /* send the packets */
			e1000_create_lbtest_frame(txdr->buffer_info[i].skb,
						  1024);
			dma_sync_single_for_device(&pdev->dev,
						   txdr->buffer_info[k].dma,
						   txdr->buffer_info[k].length,
						   DMA_TO_DEVICE);
			if (unlikely(++k == txdr->count))
				k = 0;
		}
		ew32(TDT, k);
		E1000_WRITE_FLUSH();
		msleep(200);
		time = jiffies; /* set the start time for the receive */
		good_cnt = 0;
		do { /* receive the sent packets */
			dma_sync_single_for_cpu(&pdev->dev,
						rxdr->buffer_info[l].dma,
						E1000_RXBUFFER_2048,
						DMA_FROM_DEVICE);

			ret_val = e1000_check_lbtest_frame(
					rxdr->buffer_info[l].rxbuf.data +
					NET_SKB_PAD + NET_IP_ALIGN,
					1024);
			if (!ret_val)
				good_cnt++;
			if (unlikely(++l == rxdr->count))
				l = 0;
			/* time + 20 msecs (200 msecs on 2.4) is more than
			 * enough time to complete the receives, if it's
			 * exceeded, break and error off
			 */
		} while (good_cnt < 64 && time_after(time + 20, jiffies));

		if (good_cnt != 64) {
			ret_val = 13; /* ret_val is the same as mis-compare */
			break;
		}
		if (time_after_eq(jiffies, time + 2)) {
			ret_val = 14; /* error code for time out error */
			break;
		}
	} /* end loop count loop */
	return ret_val;
}