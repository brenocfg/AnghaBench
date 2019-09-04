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
typedef  int uint32_t ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int DC_BALANCE_RESET ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int PIPE_A ; 
 int PIPE_A_SCRAMBLE_RESET ; 
 int PIPE_B_SCRAMBLE_RESET ; 
 int PIPE_SCRAMBLE_RESET_MASK ; 
 int /*<<< orphan*/  PORT_DFT2_G4X ; 
 int /*<<< orphan*/  PORT_DFT_I9XX ; 

__attribute__((used)) static void g4x_undo_pipe_scramble_reset(struct drm_i915_private *dev_priv,
					 enum pipe pipe)
{
	uint32_t tmp = I915_READ(PORT_DFT2_G4X);

	if (pipe == PIPE_A)
		tmp &= ~PIPE_A_SCRAMBLE_RESET;
	else
		tmp &= ~PIPE_B_SCRAMBLE_RESET;
	I915_WRITE(PORT_DFT2_G4X, tmp);

	if (!(tmp & PIPE_SCRAMBLE_RESET_MASK)) {
		I915_WRITE(PORT_DFT_I9XX,
			   I915_READ(PORT_DFT_I9XX) & ~DC_BALANCE_RESET);
	}
}