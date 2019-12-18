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
struct xgbe_prv_data {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  MTL_Q_RQDR ; 
 int /*<<< orphan*/  PRXQ ; 
 int /*<<< orphan*/  RXQSTS ; 
 unsigned long XGBE_DMA_STOP_TIMEOUT ; 
 scalar_t__ XGMAC_GET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int XGMAC_MTL_IOREAD (struct xgbe_prv_data*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void xgbe_prepare_rx_stop(struct xgbe_prv_data *pdata,
				 unsigned int queue)
{
	unsigned int rx_status;
	unsigned long rx_timeout;

	/* The Rx engine cannot be stopped if it is actively processing
	 * packets. Wait for the Rx queue to empty the Rx fifo.  Don't
	 * wait forever though...
	 */
	rx_timeout = jiffies + (XGBE_DMA_STOP_TIMEOUT * HZ);
	while (time_before(jiffies, rx_timeout)) {
		rx_status = XGMAC_MTL_IOREAD(pdata, queue, MTL_Q_RQDR);
		if ((XGMAC_GET_BITS(rx_status, MTL_Q_RQDR, PRXQ) == 0) &&
		    (XGMAC_GET_BITS(rx_status, MTL_Q_RQDR, RXQSTS) == 0))
			break;

		usleep_range(500, 1000);
	}

	if (!time_before(jiffies, rx_timeout))
		netdev_info(pdata->netdev,
			    "timed out waiting for Rx queue %u to empty\n",
			    queue);
}