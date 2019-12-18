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
struct sh_eth_private {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int TSU_POST1 ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int sh_eth_tsu_get_post_bit (struct sh_eth_private*,int) ; 
 int sh_eth_tsu_read (struct sh_eth_private*,int) ; 
 int /*<<< orphan*/  sh_eth_tsu_write (struct sh_eth_private*,int,int) ; 

__attribute__((used)) static void sh_eth_tsu_enable_cam_entry_post(struct net_device *ndev,
					     int entry)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	int reg = TSU_POST1 + entry / 8;
	u32 tmp;

	tmp = sh_eth_tsu_read(mdp, reg);
	sh_eth_tsu_write(mdp, tmp | sh_eth_tsu_get_post_bit(mdp, entry), reg);
}