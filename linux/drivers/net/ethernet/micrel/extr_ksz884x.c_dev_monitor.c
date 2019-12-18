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
struct timer_list {int dummy; } ;
struct net_device {int dummy; } ;
struct ksz_port {int dummy; } ;
struct ksz_hw {int features; } ;
struct TYPE_3__ {struct net_device* dev; } ;
struct dev_priv {int /*<<< orphan*/  monitor_timer_info; struct ksz_port port; struct dev_info* adapter; TYPE_1__ mii_if; } ;
struct dev_info {struct ksz_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int LINK_INT_WORKING ; 
 struct dev_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksz_update_timer (int /*<<< orphan*/ *) ; 
 TYPE_2__ monitor_timer_info ; 
 int /*<<< orphan*/  port_get_link_speed (struct ksz_port*) ; 
 struct dev_priv* priv ; 
 int /*<<< orphan*/  update_link (struct net_device*,struct dev_priv*,struct ksz_port*) ; 

__attribute__((used)) static void dev_monitor(struct timer_list *t)
{
	struct dev_priv *priv = from_timer(priv, t, monitor_timer_info.timer);
	struct net_device *dev = priv->mii_if.dev;
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_port *port = &priv->port;

	if (!(hw->features & LINK_INT_WORKING))
		port_get_link_speed(port);
	update_link(dev, priv, port);

	ksz_update_timer(&priv->monitor_timer_info);
}