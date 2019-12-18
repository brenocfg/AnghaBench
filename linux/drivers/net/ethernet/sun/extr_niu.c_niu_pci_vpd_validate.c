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
typedef  scalar_t__ u8 ;
struct niu_vpd {int /*<<< orphan*/ * local_mac; int /*<<< orphan*/  phy_type; int /*<<< orphan*/  model; } ;
struct niu {int flags; int port; int /*<<< orphan*/  device; struct niu_vpd vpd; int /*<<< orphan*/  mac_xcvr; struct net_device* dev; } ;
struct net_device {scalar_t__* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MAC_XCVR_PCS ; 
 int /*<<< orphan*/  MAC_XCVR_XPCS ; 
 int /*<<< orphan*/  NIU_ALONSO_MDL_STR ; 
 int NIU_FLAGS_10G ; 
 int NIU_FLAGS_FIBER ; 
 int NIU_FLAGS_HOTPLUG_PHY ; 
 int NIU_FLAGS_VPD_VALID ; 
 int NIU_FLAGS_XCVR_SERDES ; 
 int /*<<< orphan*/  NIU_FOXXY_MDL_STR ; 
 int /*<<< orphan*/  NIU_KIMI_MDL_STR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ niu_phy_type_prop_decode (struct niu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_pci_vpd_validate(struct niu *np)
{
	struct net_device *dev = np->dev;
	struct niu_vpd *vpd = &np->vpd;
	u8 val8;

	if (!is_valid_ether_addr(&vpd->local_mac[0])) {
		dev_err(np->device, "VPD MAC invalid, falling back to SPROM\n");

		np->flags &= ~NIU_FLAGS_VPD_VALID;
		return;
	}

	if (!strcmp(np->vpd.model, NIU_ALONSO_MDL_STR) ||
	    !strcmp(np->vpd.model, NIU_KIMI_MDL_STR)) {
		np->flags |= NIU_FLAGS_10G;
		np->flags &= ~NIU_FLAGS_FIBER;
		np->flags |= NIU_FLAGS_XCVR_SERDES;
		np->mac_xcvr = MAC_XCVR_PCS;
		if (np->port > 1) {
			np->flags |= NIU_FLAGS_FIBER;
			np->flags &= ~NIU_FLAGS_10G;
		}
		if (np->flags & NIU_FLAGS_10G)
			np->mac_xcvr = MAC_XCVR_XPCS;
	} else if (!strcmp(np->vpd.model, NIU_FOXXY_MDL_STR)) {
		np->flags |= (NIU_FLAGS_10G | NIU_FLAGS_FIBER |
			      NIU_FLAGS_HOTPLUG_PHY);
	} else if (niu_phy_type_prop_decode(np, np->vpd.phy_type)) {
		dev_err(np->device, "Illegal phy string [%s]\n",
			np->vpd.phy_type);
		dev_err(np->device, "Falling back to SPROM\n");
		np->flags &= ~NIU_FLAGS_VPD_VALID;
		return;
	}

	memcpy(dev->dev_addr, vpd->local_mac, ETH_ALEN);

	val8 = dev->dev_addr[5];
	dev->dev_addr[5] += np->port;
	if (dev->dev_addr[5] < val8)
		dev->dev_addr[4]++;
}