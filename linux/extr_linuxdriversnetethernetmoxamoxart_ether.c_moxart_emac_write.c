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
struct moxart_mac_priv_t {scalar_t__ base; } ;

/* Variables and functions */
 struct moxart_mac_priv_t* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static inline void moxart_emac_write(struct net_device *ndev,
				     unsigned int reg, unsigned long value)
{
	struct moxart_mac_priv_t *priv = netdev_priv(ndev);

	writel(value, priv->base + reg);
}