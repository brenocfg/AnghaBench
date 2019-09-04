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
typedef  int u8 ;
typedef  int u64 ;
struct config_param {int max_mac_addr; } ;
struct s2io_nic {TYPE_1__* def_mac_addr; struct config_param config; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int* mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ERR_DBG ; 
 int ETH_ALEN ; 
 int FAILURE ; 
 int /*<<< orphan*/  INFO_DBG ; 
 int S2IO_DISABLE_MAC_ENTRY ; 
 int SUCCESS ; 
 int do_s2io_add_mac (struct s2io_nic*,int,int) ; 
 int /*<<< orphan*/  do_s2io_copy_mac_addr (struct s2io_nic*,int,int) ; 
 int do_s2io_read_unicast_mc (struct s2io_nic*,int) ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int do_s2io_prog_unicast(struct net_device *dev, u8 *addr)
{
	struct s2io_nic *sp = netdev_priv(dev);
	register u64 mac_addr = 0, perm_addr = 0;
	int i;
	u64 tmp64;
	struct config_param *config = &sp->config;

	/*
	 * Set the new MAC address as the new unicast filter and reflect this
	 * change on the device address registered with the OS. It will be
	 * at offset 0.
	 */
	for (i = 0; i < ETH_ALEN; i++) {
		mac_addr <<= 8;
		mac_addr |= addr[i];
		perm_addr <<= 8;
		perm_addr |= sp->def_mac_addr[0].mac_addr[i];
	}

	/* check if the dev_addr is different than perm_addr */
	if (mac_addr == perm_addr)
		return SUCCESS;

	/* check if the mac already preset in CAM */
	for (i = 1; i < config->max_mac_addr; i++) {
		tmp64 = do_s2io_read_unicast_mc(sp, i);
		if (tmp64 == S2IO_DISABLE_MAC_ENTRY) /* CAM entry is empty */
			break;

		if (tmp64 == mac_addr) {
			DBG_PRINT(INFO_DBG,
				  "MAC addr:0x%llx already present in CAM\n",
				  (unsigned long long)mac_addr);
			return SUCCESS;
		}
	}
	if (i == config->max_mac_addr) {
		DBG_PRINT(ERR_DBG, "CAM full no space left for Unicast MAC\n");
		return FAILURE;
	}
	/* Update the internal structure with this new mac address */
	do_s2io_copy_mac_addr(sp, i, mac_addr);

	return do_s2io_add_mac(sp, mac_addr, i);
}