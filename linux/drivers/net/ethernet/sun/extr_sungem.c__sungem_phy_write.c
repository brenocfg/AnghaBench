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
struct gem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sungem_phy_write (struct gem*,int,int,int) ; 
 struct gem* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline void _sungem_phy_write(struct net_device *dev, int mii_id, int reg, int val)
{
	struct gem *gp = netdev_priv(dev);
	__sungem_phy_write(gp, mii_id, reg, val & 0xffff);
}