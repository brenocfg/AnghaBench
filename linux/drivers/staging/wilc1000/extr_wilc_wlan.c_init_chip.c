#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct wilc_vif {struct wilc* wilc; } ;
struct wilc {TYPE_1__* hif_func; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int (* hif_read_reg ) (struct wilc*,int,int*) ;int (* hif_write_reg ) (struct wilc*,int,int) ;} ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WILC_BUS_ACQUIRE_ONLY ; 
 int /*<<< orphan*/  WILC_BUS_RELEASE_ONLY ; 
 int /*<<< orphan*/  acquire_bus (struct wilc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  release_bus (struct wilc*,int /*<<< orphan*/ ) ; 
 int stub1 (struct wilc*,int,int*) ; 
 int stub2 (struct wilc*,int,int) ; 
 int stub3 (struct wilc*,int,int) ; 
 int wilc_get_chipid (struct wilc*,int) ; 

__attribute__((used)) static u32 init_chip(struct net_device *dev)
{
	u32 chipid;
	u32 reg, ret = 0;
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wilc = vif->wilc;

	acquire_bus(wilc, WILC_BUS_ACQUIRE_ONLY);

	chipid = wilc_get_chipid(wilc, true);

	if ((chipid & 0xfff) != 0xa0) {
		ret = wilc->hif_func->hif_read_reg(wilc, 0x1118, &reg);
		if (!ret) {
			netdev_err(dev, "fail read reg 0x1118\n");
			goto release;
		}
		reg |= BIT(0);
		ret = wilc->hif_func->hif_write_reg(wilc, 0x1118, reg);
		if (!ret) {
			netdev_err(dev, "fail write reg 0x1118\n");
			goto release;
		}
		ret = wilc->hif_func->hif_write_reg(wilc, 0xc0000, 0x71);
		if (!ret) {
			netdev_err(dev, "fail write reg 0xc0000\n");
			goto release;
		}
	}

release:
	release_bus(wilc, WILC_BUS_RELEASE_ONLY);

	return ret;
}