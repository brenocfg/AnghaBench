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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_GICST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_GICST_MASK ; 
 int /*<<< orphan*/  CG_GIT ; 
 int /*<<< orphan*/  R600_GICST_DFLT ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void si_program_git(struct radeon_device *rdev)
{
	WREG32_P(CG_GIT, CG_GICST(R600_GICST_DFLT), ~CG_GICST_MASK);
}