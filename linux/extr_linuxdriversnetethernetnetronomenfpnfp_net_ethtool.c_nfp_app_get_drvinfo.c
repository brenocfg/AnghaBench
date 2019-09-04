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
struct nfp_app {int /*<<< orphan*/  pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; } ;

/* Variables and functions */
 struct nfp_app* nfp_app_from_netdev (struct net_device*) ; 
 int /*<<< orphan*/  nfp_get_drvinfo (struct nfp_app*,int /*<<< orphan*/ ,char*,struct ethtool_drvinfo*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nfp_app_get_drvinfo(struct net_device *netdev, struct ethtool_drvinfo *drvinfo)
{
	struct nfp_app *app = nfp_app_from_netdev(netdev);

	strlcpy(drvinfo->bus_info, pci_name(app->pdev),
		sizeof(drvinfo->bus_info));
	nfp_get_drvinfo(app, app->pdev, "*", drvinfo);
}