#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stmmac_priv {TYPE_2__* plat; int /*<<< orphan*/  ioaddr; TYPE_1__* dev; int /*<<< orphan*/  device; struct mac_device_info* hw; } ;
struct TYPE_10__ {int addr_shift; int clk_csr_shift; void* clk_csr_mask; void* reg_mask; scalar_t__ reg_shift; void* addr_mask; int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  speed10000; int /*<<< orphan*/  speed5000; int /*<<< orphan*/  speed2500; } ;
struct TYPE_9__ {int /*<<< orphan*/  speed_mask; TYPE_3__ xgmii; int /*<<< orphan*/  speed2500; int /*<<< orphan*/  speed1000; int /*<<< orphan*/  speed100; int /*<<< orphan*/  speed10; scalar_t__ duplex; } ;
struct mac_device_info {TYPE_5__ mii; TYPE_4__ link; scalar_t__ multicast_filter_bins; scalar_t__ mcast_bits_log2; int /*<<< orphan*/  unicast_filter_entries; int /*<<< orphan*/  pcsr; } ;
struct TYPE_7__ {int /*<<< orphan*/  unicast_filter_entries; scalar_t__ multicast_filter_bins; } ;
struct TYPE_6__ {int /*<<< orphan*/  priv_flags; } ;

/* Variables and functions */
 void* GENMASK (int,int) ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int /*<<< orphan*/  XGMAC_CONFIG_SS_10000 ; 
 int /*<<< orphan*/  XGMAC_CONFIG_SS_1000_GMII ; 
 int /*<<< orphan*/  XGMAC_CONFIG_SS_100_MII ; 
 int /*<<< orphan*/  XGMAC_CONFIG_SS_10_MII ; 
 int /*<<< orphan*/  XGMAC_CONFIG_SS_2500 ; 
 int /*<<< orphan*/  XGMAC_CONFIG_SS_2500_GMII ; 
 int /*<<< orphan*/  XGMAC_CONFIG_SS_5000 ; 
 int /*<<< orphan*/  XGMAC_CONFIG_SS_MASK ; 
 int /*<<< orphan*/  XGMAC_MDIO_ADDR ; 
 int /*<<< orphan*/  XGMAC_MDIO_DATA ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ilog2 (scalar_t__) ; 

int dwxgmac2_setup(struct stmmac_priv *priv)
{
	struct mac_device_info *mac = priv->hw;

	dev_info(priv->device, "\tXGMAC2\n");

	priv->dev->priv_flags |= IFF_UNICAST_FLT;
	mac->pcsr = priv->ioaddr;
	mac->multicast_filter_bins = priv->plat->multicast_filter_bins;
	mac->unicast_filter_entries = priv->plat->unicast_filter_entries;
	mac->mcast_bits_log2 = 0;

	if (mac->multicast_filter_bins)
		mac->mcast_bits_log2 = ilog2(mac->multicast_filter_bins);

	mac->link.duplex = 0;
	mac->link.speed10 = XGMAC_CONFIG_SS_10_MII;
	mac->link.speed100 = XGMAC_CONFIG_SS_100_MII;
	mac->link.speed1000 = XGMAC_CONFIG_SS_1000_GMII;
	mac->link.speed2500 = XGMAC_CONFIG_SS_2500_GMII;
	mac->link.xgmii.speed2500 = XGMAC_CONFIG_SS_2500;
	mac->link.xgmii.speed5000 = XGMAC_CONFIG_SS_5000;
	mac->link.xgmii.speed10000 = XGMAC_CONFIG_SS_10000;
	mac->link.speed_mask = XGMAC_CONFIG_SS_MASK;

	mac->mii.addr = XGMAC_MDIO_ADDR;
	mac->mii.data = XGMAC_MDIO_DATA;
	mac->mii.addr_shift = 16;
	mac->mii.addr_mask = GENMASK(20, 16);
	mac->mii.reg_shift = 0;
	mac->mii.reg_mask = GENMASK(15, 0);
	mac->mii.clk_csr_shift = 19;
	mac->mii.clk_csr_mask = GENMASK(21, 19);

	return 0;
}