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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct vc4_validated_shader_info {int dummy; } ;
struct vc4_shader_validation_state {int needs_uniform_address_for_loop; int /*<<< orphan*/  ip; } ;
typedef  void* int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QPU_BRANCH_TARGET ; 
 void* QPU_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QPU_WADDR_ADD ; 
 int /*<<< orphan*/  QPU_WADDR_MUL ; 
 scalar_t__ QPU_W_NOP ; 

__attribute__((used)) static bool
check_branch(uint64_t inst,
	     struct vc4_validated_shader_info *validated_shader,
	     struct vc4_shader_validation_state *validation_state,
	     int ip)
{
	int32_t branch_imm = QPU_GET_FIELD(inst, QPU_BRANCH_TARGET);
	uint32_t waddr_add = QPU_GET_FIELD(inst, QPU_WADDR_ADD);
	uint32_t waddr_mul = QPU_GET_FIELD(inst, QPU_WADDR_MUL);

	if ((int)branch_imm < 0)
		validation_state->needs_uniform_address_for_loop = true;

	/* We don't want to have to worry about validation of this, and
	 * there's no need for it.
	 */
	if (waddr_add != QPU_W_NOP || waddr_mul != QPU_W_NOP) {
		DRM_DEBUG("branch instruction at %d wrote a register.\n",
			  validation_state->ip);
		return false;
	}

	return true;
}