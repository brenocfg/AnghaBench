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
struct wilc_vif {struct wilc* wilc; } ;
struct wilc {scalar_t__ dev_irq_num; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct wilc*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void deinit_irq(struct net_device *dev)
{
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wilc = vif->wilc;

	/* Deinitialize IRQ */
	if (wilc->dev_irq_num)
		free_irq(wilc->dev_irq_num, wilc);
}