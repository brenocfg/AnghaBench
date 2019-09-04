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
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
struct nb8800_priv {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  NB8800_SRC_ADDR (int) ; 
 int /*<<< orphan*/  NB8800_UC_ADDR (int) ; 
 int /*<<< orphan*/  nb8800_writeb (struct nb8800_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nb8800_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void nb8800_update_mac_addr(struct net_device *dev)
{
	struct nb8800_priv *priv = netdev_priv(dev);
	int i;

	for (i = 0; i < ETH_ALEN; i++)
		nb8800_writeb(priv, NB8800_SRC_ADDR(i), dev->dev_addr[i]);

	for (i = 0; i < ETH_ALEN; i++)
		nb8800_writeb(priv, NB8800_UC_ADDR(i), dev->dev_addr[i]);
}