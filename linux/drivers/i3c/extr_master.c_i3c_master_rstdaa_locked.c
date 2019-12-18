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
typedef  int /*<<< orphan*/  u8 ;
struct i3c_master_controller {int /*<<< orphan*/  bus; } ;
struct i3c_ccc_cmd_dest {int dummy; } ;
struct i3c_ccc_cmd {int dummy; } ;
typedef  enum i3c_addr_slot_status { ____Placeholder_i3c_addr_slot_status } i3c_addr_slot_status ;

/* Variables and functions */
 int EINVAL ; 
 int I3C_ADDR_SLOT_I3C_DEV ; 
 int /*<<< orphan*/  I3C_BROADCAST_ADDR ; 
 int /*<<< orphan*/  I3C_CCC_RSTDAA (int) ; 
 int i3c_bus_get_addr_slot_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i3c_ccc_cmd_dest_cleanup (struct i3c_ccc_cmd_dest*) ; 
 int /*<<< orphan*/  i3c_ccc_cmd_dest_init (struct i3c_ccc_cmd_dest*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i3c_ccc_cmd_init (struct i3c_ccc_cmd*,int,int /*<<< orphan*/ ,struct i3c_ccc_cmd_dest*,int) ; 
 int i3c_master_send_ccc_cmd_locked (struct i3c_master_controller*,struct i3c_ccc_cmd*) ; 

__attribute__((used)) static int i3c_master_rstdaa_locked(struct i3c_master_controller *master,
				    u8 addr)
{
	enum i3c_addr_slot_status addrstat;
	struct i3c_ccc_cmd_dest dest;
	struct i3c_ccc_cmd cmd;
	int ret;

	if (!master)
		return -EINVAL;

	addrstat = i3c_bus_get_addr_slot_status(&master->bus, addr);
	if (addr != I3C_BROADCAST_ADDR && addrstat != I3C_ADDR_SLOT_I3C_DEV)
		return -EINVAL;

	i3c_ccc_cmd_dest_init(&dest, addr, 0);
	i3c_ccc_cmd_init(&cmd, false,
			 I3C_CCC_RSTDAA(addr == I3C_BROADCAST_ADDR),
			 &dest, 1);
	ret = i3c_master_send_ccc_cmd_locked(master, &cmd);
	i3c_ccc_cmd_dest_cleanup(&dest);

	return ret;
}