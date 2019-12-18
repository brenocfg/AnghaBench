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
struct net_device {int dummy; } ;
struct cas {int /*<<< orphan*/ * stat_lock; TYPE_1__* net_stats; int /*<<< orphan*/  dev; scalar_t__ regs; } ;
struct TYPE_2__ {int rx_frame_errors; int rx_crc_errors; int rx_length_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_over_errors; } ;

/* Variables and functions */
 int MAC_RX_ALIGN_ERR ; 
 int MAC_RX_CRC_ERR ; 
 int MAC_RX_LEN_ERR ; 
 int MAC_RX_OVERFLOW ; 
 scalar_t__ REG_MAC_RX_STATUS ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  netif_dbg (struct cas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cas_rxmac_interrupt(struct net_device *dev, struct cas *cp,
			       u32 status)
{
	u32 stat = readl(cp->regs + REG_MAC_RX_STATUS);

	if (!stat)
		return 0;

	netif_dbg(cp, intr, cp->dev, "rxmac interrupt, stat: 0x%x\n", stat);

	/* these are all rollovers */
	spin_lock(&cp->stat_lock[0]);
	if (stat & MAC_RX_ALIGN_ERR)
		cp->net_stats[0].rx_frame_errors += 0x10000;

	if (stat & MAC_RX_CRC_ERR)
		cp->net_stats[0].rx_crc_errors += 0x10000;

	if (stat & MAC_RX_LEN_ERR)
		cp->net_stats[0].rx_length_errors += 0x10000;

	if (stat & MAC_RX_OVERFLOW) {
		cp->net_stats[0].rx_over_errors++;
		cp->net_stats[0].rx_fifo_errors++;
	}

	/* We do not track MAC_RX_FRAME_COUNT and MAC_RX_VIOL_ERR
	 * events.
	 */
	spin_unlock(&cp->stat_lock[0]);
	return 0;
}