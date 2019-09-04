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
typedef  int u32 ;
struct cs_hsi_iface {int dummy; } ;

/* Variables and functions */
 int CS_CMD_MASK ; 
 int CS_PARAM_MASK ; 
 int CS_TX_DATA_READY ; 
 int EINVAL ; 
#define  TARGET_LOCAL 129 
 int TARGET_MASK ; 
#define  TARGET_REMOTE 128 
 int cs_hsi_write_on_control (struct cs_hsi_iface*,int) ; 
 int cs_hsi_write_on_data (struct cs_hsi_iface*,int) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 

__attribute__((used)) static int cs_hsi_command(struct cs_hsi_iface *hi, u32 cmd)
{
	int ret = 0;

	local_bh_disable();
	switch (cmd & TARGET_MASK) {
	case TARGET_REMOTE:
		ret = cs_hsi_write_on_control(hi, cmd);
		break;
	case TARGET_LOCAL:
		if ((cmd & CS_CMD_MASK) == CS_TX_DATA_READY)
			ret = cs_hsi_write_on_data(hi, cmd & CS_PARAM_MASK);
		else
			ret = -EINVAL;
		break;
	default:
		ret = -EINVAL;
		break;
	}
	local_bh_enable();

	return ret;
}