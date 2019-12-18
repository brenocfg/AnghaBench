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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_GICST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_GICST_MASK ; 
 int /*<<< orphan*/  CG_GIT ; 
 int /*<<< orphan*/  SUMO_GICST_DFLT ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_calculate_u_and_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_get_xclk (struct radeon_device*) ; 

__attribute__((used)) static void sumo_program_git(struct radeon_device *rdev)
{
	u32 p, u;
	u32 xclk = radeon_get_xclk(rdev);

	r600_calculate_u_and_p(SUMO_GICST_DFLT,
			       xclk, 16, &p, &u);

	WREG32_P(CG_GIT, CG_GICST(p), ~CG_GICST_MASK);
}