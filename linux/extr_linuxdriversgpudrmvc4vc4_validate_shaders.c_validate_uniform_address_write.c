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
typedef  int u32 ;
struct vc4_validated_shader_info {int uniforms_size; } ;
struct vc4_shader_validation_state {int* shader; size_t ip; int* live_immediates; int needs_uniform_address_update; int needs_uniform_address_for_loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  QPU_ADD_B ; 
 int QPU_A_ADD ; 
 int /*<<< orphan*/  QPU_COND_ADD ; 
 int QPU_COND_ALWAYS ; 
 int QPU_GET_FIELD (int,int /*<<< orphan*/ ) ; 
 int QPU_MUX_A ; 
 int QPU_MUX_B ; 
 int /*<<< orphan*/  QPU_OP_ADD ; 
 int /*<<< orphan*/  QPU_PACK ; 
 int QPU_PACK_A_NOP ; 
 int QPU_PM ; 
 int /*<<< orphan*/  QPU_RADDR_A ; 
 int /*<<< orphan*/  QPU_RADDR_B ; 
 int QPU_R_UNIF ; 
 int /*<<< orphan*/  QPU_SIG ; 
#define  QPU_SIG_COLOR_LOAD 132 
#define  QPU_SIG_LOAD_TMU0 131 
#define  QPU_SIG_LOAD_TMU1 130 
#define  QPU_SIG_NONE 129 
#define  QPU_SIG_SCOREBOARD_UNLOCK 128 
 int raddr_add_a_to_live_reg_index (int) ; 
 int require_uniform_address_uniform (struct vc4_validated_shader_info*) ; 

__attribute__((used)) static bool
validate_uniform_address_write(struct vc4_validated_shader_info *validated_shader,
			       struct vc4_shader_validation_state *validation_state,
			       bool is_mul)
{
	uint64_t inst = validation_state->shader[validation_state->ip];
	u32 add_b = QPU_GET_FIELD(inst, QPU_ADD_B);
	u32 raddr_a = QPU_GET_FIELD(inst, QPU_RADDR_A);
	u32 raddr_b = QPU_GET_FIELD(inst, QPU_RADDR_B);
	u32 add_lri = raddr_add_a_to_live_reg_index(inst);
	/* We want our reset to be pointing at whatever uniform follows the
	 * uniforms base address.
	 */
	u32 expected_offset = validated_shader->uniforms_size + 4;

	/* We only support absolute uniform address changes, and we
	 * require that they be in the current basic block before any
	 * of its uniform reads.
	 *
	 * One could potentially emit more efficient QPU code, by
	 * noticing that (say) an if statement does uniform control
	 * flow for all threads and that the if reads the same number
	 * of uniforms on each side.  However, this scheme is easy to
	 * validate so it's all we allow for now.
	 */
	switch (QPU_GET_FIELD(inst, QPU_SIG)) {
	case QPU_SIG_NONE:
	case QPU_SIG_SCOREBOARD_UNLOCK:
	case QPU_SIG_COLOR_LOAD:
	case QPU_SIG_LOAD_TMU0:
	case QPU_SIG_LOAD_TMU1:
		break;
	default:
		DRM_DEBUG("uniforms address change must be "
			  "normal math\n");
		return false;
	}

	if (is_mul || QPU_GET_FIELD(inst, QPU_OP_ADD) != QPU_A_ADD) {
		DRM_DEBUG("Uniform address reset must be an ADD.\n");
		return false;
	}

	if (QPU_GET_FIELD(inst, QPU_COND_ADD) != QPU_COND_ALWAYS) {
		DRM_DEBUG("Uniform address reset must be unconditional.\n");
		return false;
	}

	if (QPU_GET_FIELD(inst, QPU_PACK) != QPU_PACK_A_NOP &&
	    !(inst & QPU_PM)) {
		DRM_DEBUG("No packing allowed on uniforms reset\n");
		return false;
	}

	if (add_lri == -1) {
		DRM_DEBUG("First argument of uniform address write must be "
			  "an immediate value.\n");
		return false;
	}

	if (validation_state->live_immediates[add_lri] != expected_offset) {
		DRM_DEBUG("Resetting uniforms with offset %db instead of %db\n",
			  validation_state->live_immediates[add_lri],
			  expected_offset);
		return false;
	}

	if (!(add_b == QPU_MUX_A && raddr_a == QPU_R_UNIF) &&
	    !(add_b == QPU_MUX_B && raddr_b == QPU_R_UNIF)) {
		DRM_DEBUG("Second argument of uniform address write must be "
			  "a uniform.\n");
		return false;
	}

	validation_state->needs_uniform_address_update = false;
	validation_state->needs_uniform_address_for_loop = false;
	return require_uniform_address_uniform(validated_shader);
}