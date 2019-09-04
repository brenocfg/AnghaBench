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
struct rv7xx_ps {TYPE_1__ high; } ;
struct radeon_ps {int dummy; } ;
typedef  enum radeon_pcie_gen { ____Placeholder_radeon_pcie_gen } radeon_pcie_gen ;

/* Variables and functions */
 int ATOM_PPLIB_R600_FLAGS_PCIEGEN2 ; 
 struct rv7xx_ps* rv770_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static enum radeon_pcie_gen cypress_get_maximum_link_speed(struct radeon_ps *radeon_state)
{
	struct rv7xx_ps *state = rv770_get_ps(radeon_state);

	if (state->high.flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2)
		return 1;
	return 0;
}