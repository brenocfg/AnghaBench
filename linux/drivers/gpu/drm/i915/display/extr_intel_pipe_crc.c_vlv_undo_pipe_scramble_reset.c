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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int DC_BALANCE_RESET_VLV ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
#define  PIPE_A 130 
 int PIPE_A_SCRAMBLE_RESET ; 
#define  PIPE_B 129 
 int PIPE_B_SCRAMBLE_RESET ; 
#define  PIPE_C 128 
 int PIPE_C_SCRAMBLE_RESET ; 
 int PIPE_SCRAMBLE_RESET_MASK ; 
 int /*<<< orphan*/  PORT_DFT2_G4X ; 

__attribute__((used)) static void vlv_undo_pipe_scramble_reset(struct drm_i915_private *dev_priv,
					 enum pipe pipe)
{
	u32 tmp = I915_READ(PORT_DFT2_G4X);

	switch (pipe) {
	case PIPE_A:
		tmp &= ~PIPE_A_SCRAMBLE_RESET;
		break;
	case PIPE_B:
		tmp &= ~PIPE_B_SCRAMBLE_RESET;
		break;
	case PIPE_C:
		tmp &= ~PIPE_C_SCRAMBLE_RESET;
		break;
	default:
		return;
	}
	if (!(tmp & PIPE_SCRAMBLE_RESET_MASK))
		tmp &= ~DC_BALANCE_RESET_VLV;
	I915_WRITE(PORT_DFT2_G4X, tmp);
}