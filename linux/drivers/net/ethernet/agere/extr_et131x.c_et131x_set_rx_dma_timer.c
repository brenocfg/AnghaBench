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
struct phy_device {scalar_t__ speed; } ;
struct et131x_adapter {TYPE_2__* regs; TYPE_1__* netdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  num_pkt_done; int /*<<< orphan*/  max_pkt_time; } ;
struct TYPE_5__ {TYPE_3__ rxdma; } ;
struct TYPE_4__ {struct phy_device* phydev; } ;

/* Variables and functions */
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void et131x_set_rx_dma_timer(struct et131x_adapter *adapter)
{
	struct phy_device *phydev = adapter->netdev->phydev;

	/* For version B silicon, we do not use the RxDMA timer for 10 and 100
	 * Mbits/s line rates. We do not enable and RxDMA interrupt coalescing.
	 */
	if ((phydev->speed == SPEED_100) || (phydev->speed == SPEED_10)) {
		writel(0, &adapter->regs->rxdma.max_pkt_time);
		writel(1, &adapter->regs->rxdma.num_pkt_done);
	}
}