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
struct mdio_ops {int dummy; } ;
struct TYPE_2__ {int prtad; } ;
struct cphy {TYPE_1__ mdio; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_STAT1 ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_AUI ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  cphy_init (struct cphy*,struct adapter*,int,int /*<<< orphan*/ *,struct mdio_ops const*,int,char*) ; 
 int /*<<< orphan*/  qt2045_ops ; 
 int /*<<< orphan*/  t3_mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

int t3_qt2045_phy_prep(struct cphy *phy, struct adapter *adapter,
		       int phy_addr, const struct mdio_ops *mdio_ops)
{
	unsigned int stat;

	cphy_init(phy, adapter, phy_addr, &qt2045_ops, mdio_ops,
		  SUPPORTED_10000baseT_Full | SUPPORTED_AUI | SUPPORTED_TP,
		  "10GBASE-CX4");

	/*
	 * Some cards where the PHY is supposed to be at address 0 actually
	 * have it at 1.
	 */
	if (!phy_addr &&
	    !t3_mdio_read(phy, MDIO_MMD_PMAPMD, MDIO_STAT1, &stat) &&
	    stat == 0xffff)
		phy->mdio.prtad = 1;
	return 0;
}