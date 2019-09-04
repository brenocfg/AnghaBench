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
struct gemini_ethernet_port {int /*<<< orphan*/  config_lock; scalar_t__ gmac_base; } ;

/* Variables and functions */
 scalar_t__ GMAC_CONFIG0 ; 
 struct gemini_ethernet_port* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void gmac_update_config0_reg(struct net_device *netdev,
				    u32 val, u32 vmask)
{
	struct gemini_ethernet_port *port = netdev_priv(netdev);
	unsigned long flags;
	u32 reg;

	spin_lock_irqsave(&port->config_lock, flags);

	reg = readl(port->gmac_base + GMAC_CONFIG0);
	reg = (reg & ~vmask) | val;
	writel(reg, port->gmac_base + GMAC_CONFIG0);

	spin_unlock_irqrestore(&port->config_lock, flags);
}