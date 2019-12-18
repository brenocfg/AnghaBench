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
typedef  int u8 ;
struct TYPE_3__ {int* command_response; } ;
struct TYPE_4__ {TYPE_1__ response; } ;
struct vub300_mmc_host {int resp_len; TYPE_2__ resp; } ;
struct mmc_command {int* resp; int opcode; } ;

/* Variables and functions */

__attribute__((used)) static void construct_request_response(struct vub300_mmc_host *vub300,
				       struct mmc_command *cmd)
{
	int resp_len = vub300->resp_len;
	int less_cmd = (17 == resp_len) ? resp_len : resp_len - 1;
	int bytes = 3 & less_cmd;
	int words = less_cmd >> 2;
	u8 *r = vub300->resp.response.command_response;
	if (bytes == 3) {
		cmd->resp[words] = (r[1 + (words << 2)] << 24)
			| (r[2 + (words << 2)] << 16)
			| (r[3 + (words << 2)] << 8);
	} else if (bytes == 2) {
		cmd->resp[words] = (r[1 + (words << 2)] << 24)
			| (r[2 + (words << 2)] << 16);
	} else if (bytes == 1) {
		cmd->resp[words] = (r[1 + (words << 2)] << 24);
	}
	while (words-- > 0) {
		cmd->resp[words] = (r[1 + (words << 2)] << 24)
			| (r[2 + (words << 2)] << 16)
			| (r[3 + (words << 2)] << 8)
			| (r[4 + (words << 2)] << 0);
	}
	if ((cmd->opcode == 53) && (0x000000FF & cmd->resp[0]))
		cmd->resp[0] &= 0xFFFFFF00;
}