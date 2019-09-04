#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct parser_exec_state {TYPE_3__* vgpu; } ;
struct TYPE_6__ {TYPE_2__* gvt; } ;
struct TYPE_4__ {int gmadr_bytes_in_cmd; } ;
struct TYPE_5__ {TYPE_1__ device_info; } ;

/* Variables and functions */
 int cmd_address_audit (struct parser_exec_state*,unsigned long,int,int) ; 
 unsigned long cmd_gma (struct parser_exec_state*,int) ; 
 int cmd_gma_hi (struct parser_exec_state*,int) ; 
 int cmd_length (struct parser_exec_state*) ; 
 int /*<<< orphan*/  cmd_reg (struct parser_exec_state*,int) ; 
 int cmd_reg_handler (struct parser_exec_state*,int /*<<< orphan*/ ,int,char*) ; 
 int cmd_val (struct parser_exec_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ gmadr_dw_number (struct parser_exec_state*) ; 

__attribute__((used)) static int cmd_handler_srm(struct parser_exec_state *s)
{
	int gmadr_bytes = s->vgpu->gvt->device_info.gmadr_bytes_in_cmd;
	unsigned long gma;
	int i, ret = 0;
	int cmd_len = cmd_length(s);

	for (i = 1; i < cmd_len;) {
		ret |= cmd_reg_handler(s, cmd_reg(s, i), i, "srm");
		if (ret)
			break;
		if (cmd_val(s, 0) & (1 << 22)) {
			gma = cmd_gma(s, i + 1);
			if (gmadr_bytes == 8)
				gma |= (cmd_gma_hi(s, i + 2)) << 32;
			ret |= cmd_address_audit(s, gma, sizeof(u32), false);
			if (ret)
				break;
		}
		i += gmadr_dw_number(s) + 1;
	}
	return ret;
}