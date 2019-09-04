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
struct nb8800_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NB8800_TXC_CR ; 
 int /*<<< orphan*/  NB8800_TX_CTL1 ; 
 int TCR_EN ; 
 int /*<<< orphan*/  TX_EN ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  nb8800_modb (struct nb8800_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nb8800_readl (struct nb8800_priv*,int /*<<< orphan*/ ) ; 
 struct nb8800_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void nb8800_mac_tx(struct net_device *dev, bool enable)
{
	struct nb8800_priv *priv = netdev_priv(dev);

	while (nb8800_readl(priv, NB8800_TXC_CR) & TCR_EN)
		cpu_relax();

	nb8800_modb(priv, NB8800_TX_CTL1, TX_EN, enable);
}