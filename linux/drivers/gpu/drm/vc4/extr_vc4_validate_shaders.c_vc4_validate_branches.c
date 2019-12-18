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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct vc4_shader_validation_state {int max_ip; int* shader; int /*<<< orphan*/  branch_targets; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  inst ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int QPU_BRANCH_REG ; 
 int QPU_BRANCH_REL ; 
 int /*<<< orphan*/  QPU_BRANCH_TARGET ; 
 void* QPU_GET_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QPU_SIG ; 
 scalar_t__ QPU_SIG_BRANCH ; 
 scalar_t__ QPU_SIG_PROG_END ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
vc4_validate_branches(struct vc4_shader_validation_state *validation_state)
{
	uint32_t max_branch_target = 0;
	int ip;
	int last_branch = -2;

	for (ip = 0; ip < validation_state->max_ip; ip++) {
		uint64_t inst = validation_state->shader[ip];
		int32_t branch_imm = QPU_GET_FIELD(inst, QPU_BRANCH_TARGET);
		uint32_t sig = QPU_GET_FIELD(inst, QPU_SIG);
		uint32_t after_delay_ip = ip + 4;
		uint32_t branch_target_ip;

		if (sig == QPU_SIG_PROG_END) {
			/* There are two delay slots after program end is
			 * signaled that are still executed, then we're
			 * finished.  validation_state->max_ip is the
			 * instruction after the last valid instruction in the
			 * program.
			 */
			validation_state->max_ip = ip + 3;
			continue;
		}

		if (sig != QPU_SIG_BRANCH)
			continue;

		if (ip - last_branch < 4) {
			DRM_DEBUG("Branch at %d during delay slots\n", ip);
			return false;
		}
		last_branch = ip;

		if (inst & QPU_BRANCH_REG) {
			DRM_DEBUG("branching from register relative "
				  "not supported\n");
			return false;
		}

		if (!(inst & QPU_BRANCH_REL)) {
			DRM_DEBUG("relative branching required\n");
			return false;
		}

		/* The actual branch target is the instruction after the delay
		 * slots, plus whatever byte offset is in the low 32 bits of
		 * the instruction.  Make sure we're not branching beyond the
		 * end of the shader object.
		 */
		if (branch_imm % sizeof(inst) != 0) {
			DRM_DEBUG("branch target not aligned\n");
			return false;
		}

		branch_target_ip = after_delay_ip + (branch_imm >> 3);
		if (branch_target_ip >= validation_state->max_ip) {
			DRM_DEBUG("Branch at %d outside of shader (ip %d/%d)\n",
				  ip, branch_target_ip,
				  validation_state->max_ip);
			return false;
		}
		set_bit(branch_target_ip, validation_state->branch_targets);

		/* Make sure that the non-branching path is also not outside
		 * the shader.
		 */
		if (after_delay_ip >= validation_state->max_ip) {
			DRM_DEBUG("Branch at %d continues past shader end "
				  "(%d/%d)\n",
				  ip, after_delay_ip, validation_state->max_ip);
			return false;
		}
		set_bit(after_delay_ip, validation_state->branch_targets);
		max_branch_target = max(max_branch_target, after_delay_ip);
	}

	if (max_branch_target > validation_state->max_ip - 3) {
		DRM_DEBUG("Branch landed after QPU_SIG_PROG_END");
		return false;
	}

	return true;
}