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
typedef  unsigned long u32 ;
struct parser_exec_state {scalar_t__ buf_addr_type; TYPE_2__* workload; int /*<<< orphan*/  ring_id; struct intel_vgpu* vgpu; } ;
struct intel_vgpu_mm {int dummy; } ;
struct TYPE_3__ {struct intel_vgpu_mm* ggtt_mm; } ;
struct intel_vgpu {int /*<<< orphan*/  gvt; TYPE_1__ gtt; } ;
struct cmd_info {scalar_t__ opcode; } ;
struct TYPE_4__ {struct intel_vgpu_mm* shadow_mm; } ;

/* Variables and functions */
 scalar_t__ BATCH_BUFFER_2ND_LEVEL_BIT (unsigned long) ; 
 int EBADRQC ; 
 int EFAULT ; 
 scalar_t__ GTT_BUFFER ; 
 unsigned long INTEL_GVT_INVALID_ADDR ; 
 scalar_t__ OP_MI_BATCH_BUFFER_END ; 
 scalar_t__ OP_MI_BATCH_BUFFER_START ; 
 scalar_t__ PPGTT_BUFFER ; 
 unsigned long cmd_val (struct parser_exec_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_gma_to_hva (struct intel_vgpu*,struct intel_vgpu_mm*,unsigned long,unsigned long,unsigned long*) ; 
 struct cmd_info* get_cmd_info (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int get_cmd_length (struct cmd_info const*,unsigned long) ; 
 unsigned long get_gma_bb_from_cmd (struct parser_exec_state*,int) ; 
 int /*<<< orphan*/  get_opcode (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,unsigned long,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int find_bb_size(struct parser_exec_state *s,
			unsigned long *bb_size,
			unsigned long *bb_end_cmd_offset)
{
	unsigned long gma = 0;
	const struct cmd_info *info;
	u32 cmd_len = 0;
	bool bb_end = false;
	struct intel_vgpu *vgpu = s->vgpu;
	u32 cmd;
	struct intel_vgpu_mm *mm = (s->buf_addr_type == GTT_BUFFER) ?
		s->vgpu->gtt.ggtt_mm : s->workload->shadow_mm;

	*bb_size = 0;
	*bb_end_cmd_offset = 0;

	/* get the start gm address of the batch buffer */
	gma = get_gma_bb_from_cmd(s, 1);
	if (gma == INTEL_GVT_INVALID_ADDR)
		return -EFAULT;

	cmd = cmd_val(s, 0);
	info = get_cmd_info(s->vgpu->gvt, cmd, s->ring_id);
	if (info == NULL) {
		gvt_vgpu_err("unknown cmd 0x%x, opcode=0x%x, addr_type=%s, ring %d, workload=%p\n",
				cmd, get_opcode(cmd, s->ring_id),
				(s->buf_addr_type == PPGTT_BUFFER) ?
				"ppgtt" : "ggtt", s->ring_id, s->workload);
		return -EBADRQC;
	}
	do {
		if (copy_gma_to_hva(s->vgpu, mm,
				gma, gma + 4, &cmd) < 0)
			return -EFAULT;
		info = get_cmd_info(s->vgpu->gvt, cmd, s->ring_id);
		if (info == NULL) {
			gvt_vgpu_err("unknown cmd 0x%x, opcode=0x%x, addr_type=%s, ring %d, workload=%p\n",
				cmd, get_opcode(cmd, s->ring_id),
				(s->buf_addr_type == PPGTT_BUFFER) ?
				"ppgtt" : "ggtt", s->ring_id, s->workload);
			return -EBADRQC;
		}

		if (info->opcode == OP_MI_BATCH_BUFFER_END) {
			bb_end = true;
		} else if (info->opcode == OP_MI_BATCH_BUFFER_START) {
			if (BATCH_BUFFER_2ND_LEVEL_BIT(cmd) == 0)
				/* chained batch buffer */
				bb_end = true;
		}

		if (bb_end)
			*bb_end_cmd_offset = *bb_size;

		cmd_len = get_cmd_length(info, cmd) << 2;
		*bb_size += cmd_len;
		gma += cmd_len;
	} while (!bb_end);

	return 0;
}