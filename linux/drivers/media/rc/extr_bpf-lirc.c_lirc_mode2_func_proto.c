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
struct bpf_prog {int dummy; } ;
struct bpf_func_proto {int dummy; } ;
typedef  enum bpf_func_id { ____Placeholder_bpf_func_id } bpf_func_id ;

/* Variables and functions */
#define  BPF_FUNC_get_prandom_u32 140 
#define  BPF_FUNC_ktime_get_ns 139 
#define  BPF_FUNC_map_delete_elem 138 
#define  BPF_FUNC_map_lookup_elem 137 
#define  BPF_FUNC_map_peek_elem 136 
#define  BPF_FUNC_map_pop_elem 135 
#define  BPF_FUNC_map_push_elem 134 
#define  BPF_FUNC_map_update_elem 133 
#define  BPF_FUNC_rc_keydown 132 
#define  BPF_FUNC_rc_pointer_rel 131 
#define  BPF_FUNC_rc_repeat 130 
#define  BPF_FUNC_tail_call 129 
#define  BPF_FUNC_trace_printk 128 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 struct bpf_func_proto const bpf_get_prandom_u32_proto ; 
 struct bpf_func_proto const* bpf_get_trace_printk_proto () ; 
 struct bpf_func_proto const bpf_ktime_get_ns_proto ; 
 struct bpf_func_proto const bpf_map_delete_elem_proto ; 
 struct bpf_func_proto const bpf_map_lookup_elem_proto ; 
 struct bpf_func_proto const bpf_map_peek_elem_proto ; 
 struct bpf_func_proto const bpf_map_pop_elem_proto ; 
 struct bpf_func_proto const bpf_map_push_elem_proto ; 
 struct bpf_func_proto const bpf_map_update_elem_proto ; 
 struct bpf_func_proto const bpf_tail_call_proto ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct bpf_func_proto const rc_keydown_proto ; 
 struct bpf_func_proto const rc_pointer_rel_proto ; 
 struct bpf_func_proto const rc_repeat_proto ; 

__attribute__((used)) static const struct bpf_func_proto *
lirc_mode2_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog)
{
	switch (func_id) {
	case BPF_FUNC_rc_repeat:
		return &rc_repeat_proto;
	case BPF_FUNC_rc_keydown:
		return &rc_keydown_proto;
	case BPF_FUNC_rc_pointer_rel:
		return &rc_pointer_rel_proto;
	case BPF_FUNC_map_lookup_elem:
		return &bpf_map_lookup_elem_proto;
	case BPF_FUNC_map_update_elem:
		return &bpf_map_update_elem_proto;
	case BPF_FUNC_map_delete_elem:
		return &bpf_map_delete_elem_proto;
	case BPF_FUNC_map_push_elem:
		return &bpf_map_push_elem_proto;
	case BPF_FUNC_map_pop_elem:
		return &bpf_map_pop_elem_proto;
	case BPF_FUNC_map_peek_elem:
		return &bpf_map_peek_elem_proto;
	case BPF_FUNC_ktime_get_ns:
		return &bpf_ktime_get_ns_proto;
	case BPF_FUNC_tail_call:
		return &bpf_tail_call_proto;
	case BPF_FUNC_get_prandom_u32:
		return &bpf_get_prandom_u32_proto;
	case BPF_FUNC_trace_printk:
		if (capable(CAP_SYS_ADMIN))
			return bpf_get_trace_printk_proto();
		/* fall through */
	default:
		return NULL;
	}
}