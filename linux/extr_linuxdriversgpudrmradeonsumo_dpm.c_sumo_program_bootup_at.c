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
 int /*<<< orphan*/  CG_AT_0 ; 
 int /*<<< orphan*/  CG_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_L_MASK ; 
 int /*<<< orphan*/  CG_R (int) ; 
 int /*<<< orphan*/  CG_R_MASK ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sumo_program_bootup_at(struct radeon_device *rdev)
{
	WREG32_P(CG_AT_0, CG_R(0xffff), ~CG_R_MASK);
	WREG32_P(CG_AT_0, CG_L(0), ~CG_L_MASK);
}