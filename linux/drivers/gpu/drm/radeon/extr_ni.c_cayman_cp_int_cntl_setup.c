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
 int /*<<< orphan*/  CP_INT_CNTL ; 
 int /*<<< orphan*/  RINGID (int) ; 
 int /*<<< orphan*/  SRBM_GFX_CNTL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cayman_cp_int_cntl_setup(struct radeon_device *rdev,
			      int ring, u32 cp_int_cntl)
{
	WREG32(SRBM_GFX_CNTL, RINGID(ring));
	WREG32(CP_INT_CNTL, cp_int_cntl);
}