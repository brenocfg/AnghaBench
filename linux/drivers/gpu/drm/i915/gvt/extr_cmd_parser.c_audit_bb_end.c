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
typedef  int /*<<< orphan*/  u32 ;
struct parser_exec_state {scalar_t__ buf_addr_type; int /*<<< orphan*/  workload; int /*<<< orphan*/  ring_id; struct intel_vgpu* vgpu; } ;
struct intel_vgpu {int /*<<< orphan*/  gvt; } ;
struct cmd_info {scalar_t__ opcode; } ;

/* Variables and functions */
 scalar_t__ BATCH_BUFFER_2ND_LEVEL_BIT (int /*<<< orphan*/ ) ; 
 int EBADRQC ; 
 scalar_t__ OP_MI_BATCH_BUFFER_END ; 
 scalar_t__ OP_MI_BATCH_BUFFER_START ; 
 scalar_t__ PPGTT_BUFFER ; 
 struct cmd_info* get_cmd_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_opcode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int audit_bb_end(struct parser_exec_state *s, void *va)
{
	struct intel_vgpu *vgpu = s->vgpu;
	u32 cmd = *(u32 *)va;
	const struct cmd_info *info;

	info = get_cmd_info(s->vgpu->gvt, cmd, s->ring_id);
	if (info == NULL) {
		gvt_vgpu_err("unknown cmd 0x%x, opcode=0x%x, addr_type=%s, ring %d, workload=%p\n",
			cmd, get_opcode(cmd, s->ring_id),
			(s->buf_addr_type == PPGTT_BUFFER) ?
			"ppgtt" : "ggtt", s->ring_id, s->workload);
		return -EBADRQC;
	}

	if ((info->opcode == OP_MI_BATCH_BUFFER_END) ||
	    ((info->opcode == OP_MI_BATCH_BUFFER_START) &&
	     (BATCH_BUFFER_2ND_LEVEL_BIT(cmd) == 0)))
		return 0;

	return -EBADRQC;
}