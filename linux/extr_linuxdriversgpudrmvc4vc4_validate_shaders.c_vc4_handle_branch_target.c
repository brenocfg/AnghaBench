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
typedef  int /*<<< orphan*/  uint32_t ;
struct vc4_shader_validation_state {int needs_uniform_address_update; int /*<<< orphan*/  branch_targets; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  reset_validation_state (struct vc4_shader_validation_state*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ texturing_in_progress (struct vc4_shader_validation_state*) ; 

__attribute__((used)) static bool
vc4_handle_branch_target(struct vc4_shader_validation_state *validation_state)
{
	uint32_t ip = validation_state->ip;

	if (!test_bit(ip, validation_state->branch_targets))
		return true;

	if (texturing_in_progress(validation_state)) {
		DRM_DEBUG("Branch target landed during TMU setup\n");
		return false;
	}

	/* Reset our live values tracking, since this instruction may have
	 * multiple predecessors.
	 *
	 * One could potentially do analysis to determine that, for
	 * example, all predecessors have a live max clamp in the same
	 * register, but we don't bother with that.
	 */
	reset_validation_state(validation_state);

	/* Since we've entered a basic block from potentially multiple
	 * predecessors, we need the uniforms address to be updated before any
	 * unforms are read.  We require that after any branch point, the next
	 * uniform to be loaded is a uniform address offset.  That uniform's
	 * offset will be marked by the uniform address register write
	 * validation, or a one-off the end-of-program check.
	 */
	validation_state->needs_uniform_address_update = true;

	return true;
}