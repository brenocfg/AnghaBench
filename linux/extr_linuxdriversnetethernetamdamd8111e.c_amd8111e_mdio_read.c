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
struct amd8111e_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd8111e_read_phy (struct amd8111e_priv*,int,int,unsigned int*) ; 
 struct amd8111e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int amd8111e_mdio_read(struct net_device *dev, int phy_id, int reg_num)
{
	struct amd8111e_priv *lp = netdev_priv(dev);
	unsigned int reg_val;

	amd8111e_read_phy(lp,phy_id,reg_num,&reg_val);
	return reg_val;

}