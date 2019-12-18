#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {unsigned char* dev_addr; } ;
struct fec_platform_data {int /*<<< orphan*/  mac; } ;
struct fec_enet_private {unsigned char dev_id; TYPE_1__* pdev; scalar_t__ hwp; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct TYPE_5__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ FEC_ADDR_HIGH ; 
 scalar_t__ FEC_ADDR_LOW ; 
 scalar_t__ FEC_FLASHMAC ; 
 int /*<<< orphan*/  IS_ERR (char const*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,unsigned char*) ; 
 struct fec_platform_data* dev_get_platdata (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,unsigned char*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (unsigned char*) ; 
 unsigned char* macaddr ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 char* of_get_mac_address (struct device_node*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void fec_get_mac(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct fec_platform_data *pdata = dev_get_platdata(&fep->pdev->dev);
	unsigned char *iap, tmpaddr[ETH_ALEN];

	/*
	 * try to get mac address in following order:
	 *
	 * 1) module parameter via kernel command line in form
	 *    fec.macaddr=0x00,0x04,0x9f,0x01,0x30,0xe0
	 */
	iap = macaddr;

	/*
	 * 2) from device tree data
	 */
	if (!is_valid_ether_addr(iap)) {
		struct device_node *np = fep->pdev->dev.of_node;
		if (np) {
			const char *mac = of_get_mac_address(np);
			if (!IS_ERR(mac))
				iap = (unsigned char *) mac;
		}
	}

	/*
	 * 3) from flash or fuse (via platform data)
	 */
	if (!is_valid_ether_addr(iap)) {
#ifdef CONFIG_M5272
		if (FEC_FLASHMAC)
			iap = (unsigned char *)FEC_FLASHMAC;
#else
		if (pdata)
			iap = (unsigned char *)&pdata->mac;
#endif
	}

	/*
	 * 4) FEC mac registers set by bootloader
	 */
	if (!is_valid_ether_addr(iap)) {
		*((__be32 *) &tmpaddr[0]) =
			cpu_to_be32(readl(fep->hwp + FEC_ADDR_LOW));
		*((__be16 *) &tmpaddr[4]) =
			cpu_to_be16(readl(fep->hwp + FEC_ADDR_HIGH) >> 16);
		iap = &tmpaddr[0];
	}

	/*
	 * 5) random mac address
	 */
	if (!is_valid_ether_addr(iap)) {
		/* Report it and use a random ethernet address instead */
		dev_err(&fep->pdev->dev, "Invalid MAC address: %pM\n", iap);
		eth_hw_addr_random(ndev);
		dev_info(&fep->pdev->dev, "Using random MAC address: %pM\n",
			 ndev->dev_addr);
		return;
	}

	memcpy(ndev->dev_addr, iap, ETH_ALEN);

	/* Adjust MAC if using macaddr */
	if (iap == macaddr)
		 ndev->dev_addr[ETH_ALEN-1] = macaddr[ETH_ALEN-1] + fep->dev_id;
}