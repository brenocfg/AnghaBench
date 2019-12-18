#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  unsigned long u32 ;
struct parser_exec_state {size_t ring_id; TYPE_4__* workload; TYPE_3__* vgpu; } ;
struct TYPE_10__ {int /*<<< orphan*/  pipe_control_notify; } ;
struct TYPE_9__ {int /*<<< orphan*/  pending_events; } ;
struct TYPE_8__ {unsigned long* hws_pga; TYPE_2__* gvt; } ;
struct TYPE_6__ {int gmadr_bytes_in_cmd; } ;
struct TYPE_7__ {TYPE_1__ device_info; } ;

/* Variables and functions */
 int GENMASK (int,int) ; 
 int PIPE_CONTROL_GLOBAL_GTT_IVB ; 
 int PIPE_CONTROL_MMIO_WRITE ; 
 int PIPE_CONTROL_NOTIFY ; 
 int PIPE_CONTROL_POST_SYNC_OP_MASK ; 
 int cmd_address_audit (struct parser_exec_state*,unsigned long,int,int) ; 
 int cmd_gma_hi (struct parser_exec_state*,int) ; 
 TYPE_5__* cmd_interrupt_events ; 
 int /*<<< orphan*/  cmd_ptr (struct parser_exec_state*,int) ; 
 int cmd_reg (struct parser_exec_state*,int) ; 
 int cmd_reg_handler (struct parser_exec_state*,int,int,char*) ; 
 int cmd_val (struct parser_exec_state*,int) ; 
 int /*<<< orphan*/  patch_value (struct parser_exec_state*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_handler_pipe_control(struct parser_exec_state *s)
{
	int gmadr_bytes = s->vgpu->gvt->device_info.gmadr_bytes_in_cmd;
	unsigned long gma;
	bool index_mode = false;
	unsigned int post_sync;
	int ret = 0;
	u32 hws_pga, val;

	post_sync = (cmd_val(s, 1) & PIPE_CONTROL_POST_SYNC_OP_MASK) >> 14;

	/* LRI post sync */
	if (cmd_val(s, 1) & PIPE_CONTROL_MMIO_WRITE)
		ret = cmd_reg_handler(s, cmd_reg(s, 2), 1, "pipe_ctrl");
	/* post sync */
	else if (post_sync) {
		if (post_sync == 2)
			ret = cmd_reg_handler(s, 0x2350, 1, "pipe_ctrl");
		else if (post_sync == 3)
			ret = cmd_reg_handler(s, 0x2358, 1, "pipe_ctrl");
		else if (post_sync == 1) {
			/* check ggtt*/
			if ((cmd_val(s, 1) & PIPE_CONTROL_GLOBAL_GTT_IVB)) {
				gma = cmd_val(s, 2) & GENMASK(31, 3);
				if (gmadr_bytes == 8)
					gma |= (cmd_gma_hi(s, 3)) << 32;
				/* Store Data Index */
				if (cmd_val(s, 1) & (1 << 21))
					index_mode = true;
				ret |= cmd_address_audit(s, gma, sizeof(u64),
						index_mode);
				if (ret)
					return ret;
				if (index_mode) {
					hws_pga = s->vgpu->hws_pga[s->ring_id];
					gma = hws_pga + gma;
					patch_value(s, cmd_ptr(s, 2), gma);
					val = cmd_val(s, 1) & (~(1 << 21));
					patch_value(s, cmd_ptr(s, 1), val);
				}
			}
		}
	}

	if (ret)
		return ret;

	if (cmd_val(s, 1) & PIPE_CONTROL_NOTIFY)
		set_bit(cmd_interrupt_events[s->ring_id].pipe_control_notify,
				s->workload->pending_events);
	return 0;
}