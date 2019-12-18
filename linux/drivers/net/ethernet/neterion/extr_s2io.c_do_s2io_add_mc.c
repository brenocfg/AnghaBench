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
typedef  int u8 ;
typedef  int u64 ;
struct config_param {int mc_start_offset; int max_mc_addr; } ;
struct s2io_nic {struct config_param config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_DBG ; 
 int ETH_ALEN ; 
 int FAILURE ; 
 int S2IO_DISABLE_MAC_ENTRY ; 
 int SUCCESS ; 
 int do_s2io_add_mac (struct s2io_nic*,int,int) ; 
 int /*<<< orphan*/  do_s2io_copy_mac_addr (struct s2io_nic*,int,int) ; 
 int do_s2io_read_unicast_mc (struct s2io_nic*,int) ; 

__attribute__((used)) static int do_s2io_add_mc(struct s2io_nic *sp, u8 *addr)
{
	int i;
	u64 mac_addr = 0;
	struct config_param *config = &sp->config;

	for (i = 0; i < ETH_ALEN; i++) {
		mac_addr <<= 8;
		mac_addr |= addr[i];
	}
	if ((0ULL == mac_addr) || (mac_addr == S2IO_DISABLE_MAC_ENTRY))
		return SUCCESS;

	/* check if the multicast mac already preset in CAM */
	for (i = config->mc_start_offset; i < config->max_mc_addr; i++) {
		u64 tmp64;
		tmp64 = do_s2io_read_unicast_mc(sp, i);
		if (tmp64 == S2IO_DISABLE_MAC_ENTRY) /* CAM entry is empty */
			break;

		if (tmp64 == mac_addr)
			return SUCCESS;
	}
	if (i == config->max_mc_addr) {
		DBG_PRINT(ERR_DBG,
			  "CAM full no space left for multicast MAC\n");
		return FAILURE;
	}
	/* Update the internal structure with this new mac address */
	do_s2io_copy_mac_addr(sp, i, mac_addr);

	return do_s2io_add_mac(sp, mac_addr, i);
}