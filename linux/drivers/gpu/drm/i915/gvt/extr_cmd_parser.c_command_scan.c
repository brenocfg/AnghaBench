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
struct parser_exec_state {unsigned long ip_gma; scalar_t__ buf_type; struct intel_vgpu* vgpu; } ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ RING_BUFFER_INSTRUCTION ; 
 int cmd_parser_exec (struct parser_exec_state*) ; 
 scalar_t__ gma_out_of_range (unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,...) ; 
 int /*<<< orphan*/  parser_exec_state_dump (struct parser_exec_state*) ; 

__attribute__((used)) static int command_scan(struct parser_exec_state *s,
		unsigned long rb_head, unsigned long rb_tail,
		unsigned long rb_start, unsigned long rb_len)
{

	unsigned long gma_head, gma_tail, gma_bottom;
	int ret = 0;
	struct intel_vgpu *vgpu = s->vgpu;

	gma_head = rb_start + rb_head;
	gma_tail = rb_start + rb_tail;
	gma_bottom = rb_start +  rb_len;

	while (s->ip_gma != gma_tail) {
		if (s->buf_type == RING_BUFFER_INSTRUCTION) {
			if (!(s->ip_gma >= rb_start) ||
				!(s->ip_gma < gma_bottom)) {
				gvt_vgpu_err("ip_gma %lx out of ring scope."
					"(base:0x%lx, bottom: 0x%lx)\n",
					s->ip_gma, rb_start,
					gma_bottom);
				parser_exec_state_dump(s);
				return -EFAULT;
			}
			if (gma_out_of_range(s->ip_gma, gma_head, gma_tail)) {
				gvt_vgpu_err("ip_gma %lx out of range."
					"base 0x%lx head 0x%lx tail 0x%lx\n",
					s->ip_gma, rb_start,
					rb_head, rb_tail);
				parser_exec_state_dump(s);
				break;
			}
		}
		ret = cmd_parser_exec(s);
		if (ret) {
			gvt_vgpu_err("cmd parser error\n");
			parser_exec_state_dump(s);
			break;
		}
	}

	return ret;
}