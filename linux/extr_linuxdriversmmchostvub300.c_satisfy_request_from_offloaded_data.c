#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct vub300_mmc_host {size_t dynamic_register_count; scalar_t__ total_offload_count; TYPE_2__* fn; TYPE_1__* sdio_register; } ;
struct mmc_command {int arg; size_t* resp; } ;
struct TYPE_4__ {scalar_t__ offload_count; } ;
struct TYPE_3__ {size_t func_num; scalar_t__ sdio_reg; size_t response; size_t regvalue; scalar_t__ prepared; } ;

/* Variables and functions */
 size_t FUN (struct mmc_command*) ; 
 scalar_t__ REG (struct mmc_command*) ; 
 int examine_cyclic_buffer (struct vub300_mmc_host*,struct mmc_command*,size_t) ; 

__attribute__((used)) static int satisfy_request_from_offloaded_data(struct vub300_mmc_host *vub300,
					       struct mmc_command *cmd)
{
	/* cmd_mutex is held by vub300_mmc_request */
	u8 regs = vub300->dynamic_register_count;
	u8 i = 0;
	u8 func = FUN(cmd);
	u32 reg = REG(cmd);
	while (0 < regs--) {
		if ((vub300->sdio_register[i].func_num == func) &&
		    (vub300->sdio_register[i].sdio_reg == reg)) {
			if (!vub300->sdio_register[i].prepared) {
				return 0;
			} else if ((0x80000000 & cmd->arg) == 0x80000000) {
				/*
				 * a write to a dynamic register
				 * nullifies our offloaded value
				 */
				vub300->sdio_register[i].prepared = 0;
				return 0;
			} else {
				u8 checksum = 0x00;
				u8 rsp0 = 0x00;
				u8 rsp1 = 0x00;
				u8 rsp2 = vub300->sdio_register[i].response;
				u8 rsp3 = vub300->sdio_register[i].regvalue;
				vub300->sdio_register[i].prepared = 0;
				cmd->resp[1] = checksum << 24;
				cmd->resp[0] = (rsp0 << 24)
					| (rsp1 << 16)
					| (rsp2 << 8)
					| (rsp3 << 0);
				return 1;
			}
		} else {
			i += 1;
			continue;
		}
	}
	if (vub300->total_offload_count == 0)
		return 0;
	else if (vub300->fn[func].offload_count == 0)
		return 0;
	else
		return examine_cyclic_buffer(vub300, cmd, func);
}