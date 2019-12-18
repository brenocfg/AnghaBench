#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;
struct rv6xx_ps {TYPE_1__ low; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE ; 
 int /*<<< orphan*/  BACKBIAS_VALUE ; 
 int /*<<< orphan*/  GENERAL_PWRMGT ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rv6xx_ps* rv6xx_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void rv6xx_set_safe_backbias(struct radeon_device *rdev,
				    struct radeon_ps *new_ps,
				    struct radeon_ps *old_ps)
{
	struct rv6xx_ps *new_state = rv6xx_get_ps(new_ps);
	struct rv6xx_ps *old_state = rv6xx_get_ps(old_ps);

	if ((new_state->low.flags & ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE) &&
	    (old_state->low.flags & ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE))
		WREG32_P(GENERAL_PWRMGT, BACKBIAS_VALUE, ~BACKBIAS_VALUE);
	else
		WREG32_P(GENERAL_PWRMGT, 0, ~BACKBIAS_VALUE);
}