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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac_addr; } ;
struct adapter {TYPE_1__ eeprompriv; int /*<<< orphan*/  bup; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 

__attribute__((used)) static int rtw_net_set_mac_address(struct net_device *pnetdev, void *p)
{
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(pnetdev);
	struct sockaddr *addr = p;

	if (!padapter->bup)
		memcpy(padapter->eeprompriv.mac_addr, addr->sa_data, ETH_ALEN);

	return 0;
}