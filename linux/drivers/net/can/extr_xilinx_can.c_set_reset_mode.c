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
struct xcan_priv {int (* read_reg ) (struct xcan_priv*,int /*<<< orphan*/ ) ;scalar_t__ tx_tail; scalar_t__ tx_head; int /*<<< orphan*/  (* write_reg ) (struct xcan_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  XCAN_SRR_OFFSET ; 
 int /*<<< orphan*/  XCAN_SRR_RESET_MASK ; 
 int XCAN_SR_CONFIG_MASK ; 
 int /*<<< orphan*/  XCAN_SR_OFFSET ; 
 unsigned long XCAN_TIMEOUT ; 
 unsigned long jiffies ; 
 struct xcan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  stub1 (struct xcan_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct xcan_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int set_reset_mode(struct net_device *ndev)
{
	struct xcan_priv *priv = netdev_priv(ndev);
	unsigned long timeout;

	priv->write_reg(priv, XCAN_SRR_OFFSET, XCAN_SRR_RESET_MASK);

	timeout = jiffies + XCAN_TIMEOUT;
	while (!(priv->read_reg(priv, XCAN_SR_OFFSET) & XCAN_SR_CONFIG_MASK)) {
		if (time_after(jiffies, timeout)) {
			netdev_warn(ndev, "timed out for config mode\n");
			return -ETIMEDOUT;
		}
		usleep_range(500, 10000);
	}

	/* reset clears FIFOs */
	priv->tx_head = 0;
	priv->tx_tail = 0;

	return 0;
}