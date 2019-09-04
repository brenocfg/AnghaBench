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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct cc770_priv {int /*<<< orphan*/  irq_flags; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  cc770_interrupt ; 
 int /*<<< orphan*/  cc770_start (struct net_device*) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 struct cc770_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  set_reset_mode (struct net_device*) ; 

__attribute__((used)) static int cc770_open(struct net_device *dev)
{
	struct cc770_priv *priv = netdev_priv(dev);
	int err;

	/* set chip into reset mode */
	set_reset_mode(dev);

	/* common open */
	err = open_candev(dev);
	if (err)
		return err;

	err = request_irq(dev->irq, &cc770_interrupt, priv->irq_flags,
			  dev->name, dev);
	if (err) {
		close_candev(dev);
		return -EAGAIN;
	}

	/* init and start chip */
	cc770_start(dev);

	netif_start_queue(dev);

	return 0;
}