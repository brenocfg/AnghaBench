#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* spi; } ;
struct encx24j600_priv {TYPE_2__ ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  encx24j600_hw_disable (struct encx24j600_priv*) ; 
 int /*<<< orphan*/  encx24j600_hw_enable (struct encx24j600_priv*) ; 
 int /*<<< orphan*/  encx24j600_hw_init (struct encx24j600_priv*) ; 
 int /*<<< orphan*/  encx24j600_isr ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ,int) ; 
 struct encx24j600_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct encx24j600_priv*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int encx24j600_open(struct net_device *dev)
{
	struct encx24j600_priv *priv = netdev_priv(dev);

	int ret = request_threaded_irq(priv->ctx.spi->irq, NULL, encx24j600_isr,
				       IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				       DRV_NAME, priv);
	if (unlikely(ret < 0)) {
		netdev_err(dev, "request irq %d failed (ret = %d)\n",
			   priv->ctx.spi->irq, ret);
		return ret;
	}

	encx24j600_hw_disable(priv);
	encx24j600_hw_init(priv);
	encx24j600_hw_enable(priv);
	netif_start_queue(dev);

	return 0;
}