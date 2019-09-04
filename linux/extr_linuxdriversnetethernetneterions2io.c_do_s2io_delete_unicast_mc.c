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
typedef  scalar_t__ u64 ;
struct config_param {int max_mc_addr; } ;
struct s2io_nic {struct config_param config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  ERR_DBG ; 
 scalar_t__ FAILURE ; 
 scalar_t__ S2IO_DISABLE_MAC_ENTRY ; 
 int SUCCESS ; 
 scalar_t__ do_s2io_add_mac (struct s2io_nic*,scalar_t__,int) ; 
 scalar_t__ do_s2io_read_unicast_mc (struct s2io_nic*,int) ; 
 int /*<<< orphan*/  do_s2io_store_unicast_mc (struct s2io_nic*) ; 

__attribute__((used)) static int do_s2io_delete_unicast_mc(struct s2io_nic *sp, u64 addr)
{
	int offset;
	u64 dis_addr = S2IO_DISABLE_MAC_ENTRY, tmp64;
	struct config_param *config = &sp->config;

	for (offset = 1;
	     offset < config->max_mc_addr; offset++) {
		tmp64 = do_s2io_read_unicast_mc(sp, offset);
		if (tmp64 == addr) {
			/* disable the entry by writing  0xffffffffffffULL */
			if (do_s2io_add_mac(sp, dis_addr, offset) ==  FAILURE)
				return FAILURE;
			/* store the new mac list from CAM */
			do_s2io_store_unicast_mc(sp);
			return SUCCESS;
		}
	}
	DBG_PRINT(ERR_DBG, "MAC address 0x%llx not found in CAM\n",
		  (unsigned long long)addr);
	return FAILURE;
}