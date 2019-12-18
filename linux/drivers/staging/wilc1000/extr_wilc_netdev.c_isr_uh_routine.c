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
struct wilc {scalar_t__ close; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static irqreturn_t isr_uh_routine(int irq, void *user_data)
{
	struct net_device *dev = user_data;
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wilc = vif->wilc;

	if (wilc->close) {
		netdev_err(dev, "Can't handle UH interrupt\n");
		return IRQ_HANDLED;
	}
	return IRQ_WAKE_THREAD;
}