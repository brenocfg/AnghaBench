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
struct net_device {int dummy; } ;
struct cpmac_priv {int /*<<< orphan*/  regs; int /*<<< orphan*/  reset_pending; int /*<<< orphan*/  reset_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPMAC_MAC_INT_CLEAR ; 
 int /*<<< orphan*/  CPMAC_MAC_STATUS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpmac_dump_regs (struct net_device*) ; 
 int /*<<< orphan*/  cpmac_hw_stop (struct net_device*) ; 
 int cpmac_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpmac_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ net_ratelimit () ; 
 struct cpmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int,int,int) ; 
 scalar_t__ netif_msg_drv (struct cpmac_priv*) ; 
 int /*<<< orphan*/  netif_msg_hw (struct cpmac_priv*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 scalar_t__ schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpmac_check_status(struct net_device *dev)
{
	struct cpmac_priv *priv = netdev_priv(dev);

	u32 macstatus = cpmac_read(priv->regs, CPMAC_MAC_STATUS);
	int rx_channel = (macstatus >> 8) & 7;
	int rx_code = (macstatus >> 12) & 15;
	int tx_channel = (macstatus >> 16) & 7;
	int tx_code = (macstatus >> 20) & 15;

	if (rx_code || tx_code) {
		if (netif_msg_drv(priv) && net_ratelimit()) {
			/* Can't find any documentation on what these
			 * error codes actually are. So just log them and hope..
			 */
			if (rx_code)
				netdev_warn(dev, "host error %d on rx "
					"channel %d (macstatus %08x), resetting\n",
					rx_code, rx_channel, macstatus);
			if (tx_code)
				netdev_warn(dev, "host error %d on tx "
					"channel %d (macstatus %08x), resetting\n",
					tx_code, tx_channel, macstatus);
		}

		netif_tx_stop_all_queues(dev);
		cpmac_hw_stop(dev);
		if (schedule_work(&priv->reset_work))
			atomic_inc(&priv->reset_pending);
		if (unlikely(netif_msg_hw(priv)))
			cpmac_dump_regs(dev);
	}
	cpmac_write(priv->regs, CPMAC_MAC_INT_CLEAR, 0xff);
}