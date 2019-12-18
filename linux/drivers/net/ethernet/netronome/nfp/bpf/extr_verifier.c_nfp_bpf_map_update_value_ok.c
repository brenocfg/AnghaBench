#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nfp_bpf_map {TYPE_4__* use_map; } ;
struct bpf_verifier_env {TYPE_1__* cur_state; } ;
struct bpf_stack_state {scalar_t__* slot_type; } ;
struct TYPE_6__ {int value; } ;
struct bpf_reg_state {size_t frameno; int off; TYPE_2__ var_off; int /*<<< orphan*/  map_ptr; } ;
struct TYPE_7__ {int value_size; } ;
struct bpf_offloaded_map {TYPE_3__ map; struct nfp_bpf_map* dev_priv; } ;
struct bpf_func_state {struct bpf_stack_state* stack; } ;
struct TYPE_8__ {scalar_t__ type; int non_zero_update; } ;
struct TYPE_5__ {struct bpf_func_state** frame; } ;

/* Variables and functions */
 int BPF_REG_1 ; 
 int BPF_REG_3 ; 
 unsigned int BPF_REG_SIZE ; 
 scalar_t__ NFP_MAP_USE_ATOMIC_CNT ; 
 scalar_t__ STACK_ZERO ; 
 struct bpf_reg_state* cur_regs (struct bpf_verifier_env*) ; 
 struct bpf_offloaded_map* map_to_offmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_vlog (struct bpf_verifier_env*,char*,int,unsigned int) ; 

__attribute__((used)) static bool nfp_bpf_map_update_value_ok(struct bpf_verifier_env *env)
{
	const struct bpf_reg_state *reg1 = cur_regs(env) + BPF_REG_1;
	const struct bpf_reg_state *reg3 = cur_regs(env) + BPF_REG_3;
	struct bpf_offloaded_map *offmap;
	struct bpf_func_state *state;
	struct nfp_bpf_map *nfp_map;
	int off, i;

	state = env->cur_state->frame[reg3->frameno];

	/* We need to record each time update happens with non-zero words,
	 * in case such word is used in atomic operations.
	 * Implicitly depend on nfp_bpf_stack_arg_ok(reg3) being run before.
	 */

	offmap = map_to_offmap(reg1->map_ptr);
	nfp_map = offmap->dev_priv;
	off = reg3->off + reg3->var_off.value;

	for (i = 0; i < offmap->map.value_size; i++) {
		struct bpf_stack_state *stack_entry;
		unsigned int soff;

		soff = -(off + i) - 1;
		stack_entry = &state->stack[soff / BPF_REG_SIZE];
		if (stack_entry->slot_type[soff % BPF_REG_SIZE] == STACK_ZERO)
			continue;

		if (nfp_map->use_map[i / 4].type == NFP_MAP_USE_ATOMIC_CNT) {
			pr_vlog(env, "value at offset %d/%d may be non-zero, bpf_map_update_elem() is required to initialize atomic counters to zero to avoid offload endian issues\n",
				i, soff);
			return false;
		}
		nfp_map->use_map[i / 4].non_zero_update = 1;
	}

	return true;
}