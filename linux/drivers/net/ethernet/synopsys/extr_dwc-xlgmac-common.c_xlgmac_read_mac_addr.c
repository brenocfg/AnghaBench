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
struct xlgmac_pdata {int /*<<< orphan*/  mac_addr; struct net_device* netdev; } ;
struct net_device {int /*<<< orphan*/  addr_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_addr ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xlgmac_read_mac_addr(struct xlgmac_pdata *pdata)
{
	struct net_device *netdev = pdata->netdev;

	/* Currently it uses a static mac address for test */
	memcpy(pdata->mac_addr, dev_addr, netdev->addr_len);
}