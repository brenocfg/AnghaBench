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
struct parser_exec_state {size_t ring_id; TYPE_4__* workload; TYPE_3__* vgpu; } ;
struct TYPE_10__ {int /*<<< orphan*/  mi_flush_dw; } ;
struct TYPE_9__ {int /*<<< orphan*/  pending_events; } ;
struct TYPE_8__ {TYPE_2__* gvt; } ;
struct TYPE_6__ {int gmadr_bytes_in_cmd; } ;
struct TYPE_7__ {TYPE_1__ device_info; } ;

/* Variables and functions */
 int GENMASK (int,int) ; 
 int cmd_address_audit (struct parser_exec_state*,unsigned long,int,int) ; 
 TYPE_5__* cmd_interrupt_events ; 
 int cmd_val (struct parser_exec_state*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_handler_mi_flush_dw(struct parser_exec_state *s)
{
	int gmadr_bytes = s->vgpu->gvt->device_info.gmadr_bytes_in_cmd;
	unsigned long gma;
	bool index_mode = false;
	int ret = 0;

	/* Check post-sync and ppgtt bit */
	if (((cmd_val(s, 0) >> 14) & 0x3) && (cmd_val(s, 1) & (1 << 2))) {
		gma = cmd_val(s, 1) & GENMASK(31, 3);
		if (gmadr_bytes == 8)
			gma |= (cmd_val(s, 2) & GENMASK(15, 0)) << 32;
		/* Store Data Index */
		if (cmd_val(s, 0) & (1 << 21))
			index_mode = true;
		ret = cmd_address_audit(s, gma, sizeof(u64), index_mode);
	}
	/* Check notify bit */
	if ((cmd_val(s, 0) & (1 << 8)))
		set_bit(cmd_interrupt_events[s->ring_id].mi_flush_dw,
				s->workload->pending_events);
	return ret;
}