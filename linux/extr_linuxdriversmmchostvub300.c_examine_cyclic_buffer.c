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
typedef  size_t u8 ;
typedef  int u32 ;
struct vub300_mmc_host {int total_offload_count; TYPE_1__* fn; } ;
struct offload_registers_access {size_t* command_byte; int* Respond_Byte; } ;
struct mmc_command {int arg; size_t* resp; } ;
struct TYPE_2__ {int offload_point; size_t offload_count; struct offload_registers_access* reg; } ;

/* Variables and functions */
 int MAXREGMASK ; 

__attribute__((used)) static int examine_cyclic_buffer(struct vub300_mmc_host *vub300,
				 struct mmc_command *cmd, u8 Function)
{
	/* cmd_mutex is held by vub300_mmc_request */
	u8 cmd0 = 0xFF & (cmd->arg >> 24);
	u8 cmd1 = 0xFF & (cmd->arg >> 16);
	u8 cmd2 = 0xFF & (cmd->arg >> 8);
	u8 cmd3 = 0xFF & (cmd->arg >> 0);
	int first = MAXREGMASK & vub300->fn[Function].offload_point;
	struct offload_registers_access *rf = &vub300->fn[Function].reg[first];
	if (cmd0 == rf->command_byte[0] &&
	    cmd1 == rf->command_byte[1] &&
	    cmd2 == rf->command_byte[2] &&
	    cmd3 == rf->command_byte[3]) {
		u8 checksum = 0x00;
		cmd->resp[1] = checksum << 24;
		cmd->resp[0] = (rf->Respond_Byte[0] << 24)
			| (rf->Respond_Byte[1] << 16)
			| (rf->Respond_Byte[2] << 8)
			| (rf->Respond_Byte[3] << 0);
		vub300->fn[Function].offload_point += 1;
		vub300->fn[Function].offload_count -= 1;
		vub300->total_offload_count -= 1;
		return 1;
	} else {
		int delta = 1;	/* because it does not match the first one */
		u8 register_count = vub300->fn[Function].offload_count - 1;
		u32 register_point = vub300->fn[Function].offload_point + 1;
		while (0 < register_count) {
			int point = MAXREGMASK & register_point;
			struct offload_registers_access *r =
				&vub300->fn[Function].reg[point];
			if (cmd0 == r->command_byte[0] &&
			    cmd1 == r->command_byte[1] &&
			    cmd2 == r->command_byte[2] &&
			    cmd3 == r->command_byte[3]) {
				u8 checksum = 0x00;
				cmd->resp[1] = checksum << 24;
				cmd->resp[0] = (r->Respond_Byte[0] << 24)
					| (r->Respond_Byte[1] << 16)
					| (r->Respond_Byte[2] << 8)
					| (r->Respond_Byte[3] << 0);
				vub300->fn[Function].offload_point += delta;
				vub300->fn[Function].offload_count -= delta;
				vub300->total_offload_count -= delta;
				return 1;
			} else {
				register_point += 1;
				register_count -= 1;
				delta += 1;
				continue;
			}
		}
		return 0;
	}
}