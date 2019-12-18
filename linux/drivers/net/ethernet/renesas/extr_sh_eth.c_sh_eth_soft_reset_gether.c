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
struct sh_eth_private {TYPE_1__* cd; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ select_mii; scalar_t__ csmr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSMR ; 
 int /*<<< orphan*/  EDMR ; 
 int /*<<< orphan*/  EDMR_SRST_GETHER ; 
 int /*<<< orphan*/  EDSR ; 
 int /*<<< orphan*/  EDSR_ENALL ; 
 int /*<<< orphan*/  RDFAR ; 
 int /*<<< orphan*/  RDFFR ; 
 int /*<<< orphan*/  RDFXR ; 
 int /*<<< orphan*/  RDLAR ; 
 int /*<<< orphan*/  TDFAR ; 
 int /*<<< orphan*/  TDFFR ; 
 int /*<<< orphan*/  TDFXR ; 
 int /*<<< orphan*/  TDLAR ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int sh_eth_check_soft_reset (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_modify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_eth_select_mii (struct net_device*) ; 
 int /*<<< orphan*/  sh_eth_write (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_eth_soft_reset_gether(struct net_device *ndev)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	int ret;

	sh_eth_write(ndev, EDSR_ENALL, EDSR);
	sh_eth_modify(ndev, EDMR, EDMR_SRST_GETHER, EDMR_SRST_GETHER);

	ret = sh_eth_check_soft_reset(ndev);
	if (ret)
		return ret;

	/* Table Init */
	sh_eth_write(ndev, 0, TDLAR);
	sh_eth_write(ndev, 0, TDFAR);
	sh_eth_write(ndev, 0, TDFXR);
	sh_eth_write(ndev, 0, TDFFR);
	sh_eth_write(ndev, 0, RDLAR);
	sh_eth_write(ndev, 0, RDFAR);
	sh_eth_write(ndev, 0, RDFXR);
	sh_eth_write(ndev, 0, RDFFR);

	/* Reset HW CRC register */
	if (mdp->cd->csmr)
		sh_eth_write(ndev, 0, CSMR);

	/* Select MII mode */
	if (mdp->cd->select_mii)
		sh_eth_select_mii(ndev);

	return ret;
}