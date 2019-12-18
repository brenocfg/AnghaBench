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
struct ag71xx {int /*<<< orphan*/  ndev; } ;
struct TYPE_2__ {unsigned long trans_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_FIFO_DEPTH ; 
 int /*<<< orphan*/  AG71XX_REG_RX_SM ; 
 int /*<<< orphan*/  AG71XX_REG_TX_SM ; 
 int HZ ; 
 int ag71xx_rr (struct ag71xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_before (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static bool ag71xx_check_dma_stuck(struct ag71xx *ag)
{
	unsigned long timestamp;
	u32 rx_sm, tx_sm, rx_fd;

	timestamp = netdev_get_tx_queue(ag->ndev, 0)->trans_start;
	if (likely(time_before(jiffies, timestamp + HZ / 10)))
		return false;

	if (!netif_carrier_ok(ag->ndev))
		return false;

	rx_sm = ag71xx_rr(ag, AG71XX_REG_RX_SM);
	if ((rx_sm & 0x7) == 0x3 && ((rx_sm >> 4) & 0x7) == 0x6)
		return true;

	tx_sm = ag71xx_rr(ag, AG71XX_REG_TX_SM);
	rx_fd = ag71xx_rr(ag, AG71XX_REG_FIFO_DEPTH);
	if (((tx_sm >> 4) & 0x7) == 0 && ((rx_sm & 0x7) == 0) &&
	    ((rx_sm >> 4) & 0x7) == 0 && rx_fd == 0)
		return true;

	return false;
}