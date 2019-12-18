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
struct parser_exec_state {scalar_t__ buf_type; scalar_t__ ip_va; scalar_t__ ret_bb_va; scalar_t__ ip_gma; scalar_t__ ret_ip_gma_bb; scalar_t__ ret_ip_gma_ring; int /*<<< orphan*/  buf_addr_type; int /*<<< orphan*/  saved_buf_addr_type; struct intel_vgpu* vgpu; } ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ BATCH_BUFFER_2ND_LEVEL ; 
 int BATCH_BUFFER_2ND_LEVEL_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ BATCH_BUFFER_INSTRUCTION ; 
 int EFAULT ; 
 scalar_t__ RING_BUFFER_INSTRUCTION ; 
 int /*<<< orphan*/  addr_type_update_snb (struct parser_exec_state*) ; 
 scalar_t__ batch_buffer_needs_scan (struct parser_exec_state*) ; 
 int cmd_handler_mi_batch_buffer_end (struct parser_exec_state*) ; 
 int cmd_length (struct parser_exec_state*) ; 
 int /*<<< orphan*/  cmd_val (struct parser_exec_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 int perform_bb_shadow (struct parser_exec_state*) ; 

__attribute__((used)) static int cmd_handler_mi_batch_buffer_start(struct parser_exec_state *s)
{
	bool second_level;
	int ret = 0;
	struct intel_vgpu *vgpu = s->vgpu;

	if (s->buf_type == BATCH_BUFFER_2ND_LEVEL) {
		gvt_vgpu_err("Found MI_BATCH_BUFFER_START in 2nd level BB\n");
		return -EFAULT;
	}

	second_level = BATCH_BUFFER_2ND_LEVEL_BIT(cmd_val(s, 0)) == 1;
	if (second_level && (s->buf_type != BATCH_BUFFER_INSTRUCTION)) {
		gvt_vgpu_err("Jumping to 2nd level BB from RB is not allowed\n");
		return -EFAULT;
	}

	s->saved_buf_addr_type = s->buf_addr_type;
	addr_type_update_snb(s);
	if (s->buf_type == RING_BUFFER_INSTRUCTION) {
		s->ret_ip_gma_ring = s->ip_gma + cmd_length(s) * sizeof(u32);
		s->buf_type = BATCH_BUFFER_INSTRUCTION;
	} else if (second_level) {
		s->buf_type = BATCH_BUFFER_2ND_LEVEL;
		s->ret_ip_gma_bb = s->ip_gma + cmd_length(s) * sizeof(u32);
		s->ret_bb_va = s->ip_va + cmd_length(s) * sizeof(u32);
	}

	if (batch_buffer_needs_scan(s)) {
		ret = perform_bb_shadow(s);
		if (ret < 0)
			gvt_vgpu_err("invalid shadow batch buffer\n");
	} else {
		/* emulate a batch buffer end to do return right */
		ret = cmd_handler_mi_batch_buffer_end(s);
		if (ret < 0)
			return ret;
	}
	return ret;
}