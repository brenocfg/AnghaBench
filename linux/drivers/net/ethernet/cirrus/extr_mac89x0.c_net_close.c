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
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  PP_BufCFG ; 
 int /*<<< orphan*/  PP_BusCTL ; 
 int /*<<< orphan*/  PP_RxCFG ; 
 int /*<<< orphan*/  PP_TxCFG ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  writereg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
net_close(struct net_device *dev)
{

	writereg(dev, PP_RxCFG, 0);
	writereg(dev, PP_TxCFG, 0);
	writereg(dev, PP_BufCFG, 0);
	writereg(dev, PP_BusCTL, 0);

	netif_stop_queue(dev);

	free_irq(dev->irq, dev);

	/* Update the statistics here. */

	return 0;

}