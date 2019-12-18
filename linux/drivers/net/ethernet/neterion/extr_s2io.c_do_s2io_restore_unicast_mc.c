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
struct config_param {int max_mac_addr; int mc_start_offset; int max_mc_addr; } ;
struct s2io_nic {TYPE_1__* def_mac_addr; int /*<<< orphan*/  dev; struct config_param config; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_s2io_add_mc (struct s2io_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_s2io_prog_unicast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_s2io_restore_unicast_mc(struct s2io_nic *sp)
{
	int offset;
	struct config_param *config = &sp->config;
	/* restore unicast mac address */
	for (offset = 0; offset < config->max_mac_addr; offset++)
		do_s2io_prog_unicast(sp->dev,
				     sp->def_mac_addr[offset].mac_addr);

	/* restore multicast mac address */
	for (offset = config->mc_start_offset;
	     offset < config->max_mc_addr; offset++)
		do_s2io_add_mc(sp, sp->def_mac_addr[offset].mac_addr);
}