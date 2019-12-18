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
struct xlgmac_pdata {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  MTL_Q_RQDR ; 
 int /*<<< orphan*/  MTL_Q_RQDR_PRXQ_LEN ; 
 int /*<<< orphan*/  MTL_Q_RQDR_PRXQ_POS ; 
 int /*<<< orphan*/  MTL_Q_RQDR_RXQSTS_LEN ; 
 int /*<<< orphan*/  MTL_Q_RQDR_RXQSTS_POS ; 
 unsigned long XLGMAC_DMA_STOP_TIMEOUT ; 
 unsigned int XLGMAC_GET_REG_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLGMAC_MTL_REG (struct xlgmac_pdata*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void xlgmac_prepare_rx_stop(struct xlgmac_pdata *pdata,
				   unsigned int queue)
{
	unsigned int rx_status, prxq, rxqsts;
	unsigned long rx_timeout;

	/* The Rx engine cannot be stopped if it is actively processing
	 * packets. Wait for the Rx queue to empty the Rx fifo.  Don't
	 * wait forever though...
	 */
	rx_timeout = jiffies + (XLGMAC_DMA_STOP_TIMEOUT * HZ);
	while (time_before(jiffies, rx_timeout)) {
		rx_status = readl(XLGMAC_MTL_REG(pdata, queue, MTL_Q_RQDR));
		prxq = XLGMAC_GET_REG_BITS(rx_status, MTL_Q_RQDR_PRXQ_POS,
					   MTL_Q_RQDR_PRXQ_LEN);
		rxqsts = XLGMAC_GET_REG_BITS(rx_status, MTL_Q_RQDR_RXQSTS_POS,
					     MTL_Q_RQDR_RXQSTS_LEN);
		if ((prxq == 0) && (rxqsts == 0))
			break;

		usleep_range(500, 1000);
	}

	if (!time_before(jiffies, rx_timeout))
		netdev_info(pdata->netdev,
			    "timed out waiting for Rx queue %u to empty\n",
			    queue);
}