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
struct net_device {int dummy; } ;
struct ftgmac100 {int /*<<< orphan*/  reset_task; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ FTGMAC100_OFFSET_IER ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ftgmac100* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ftgmac100_tx_timeout(struct net_device *netdev)
{
	struct ftgmac100 *priv = netdev_priv(netdev);

	/* Disable all interrupts */
	iowrite32(0, priv->base + FTGMAC100_OFFSET_IER);

	/* Do the reset outside of interrupt context */
	schedule_work(&priv->reset_task);
}