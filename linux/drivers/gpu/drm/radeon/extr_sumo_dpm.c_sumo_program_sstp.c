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
 int /*<<< orphan*/  CG_SSP ; 
 int SST (int /*<<< orphan*/ ) ; 
 int SSTU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUMO_SST_DFLT ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r600_calculate_u_and_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_get_xclk (struct radeon_device*) ; 

void sumo_program_sstp(struct radeon_device *rdev)
{
	u32 p, u;
	u32 xclk = radeon_get_xclk(rdev);

	r600_calculate_u_and_p(SUMO_SST_DFLT,
			       xclk, 16, &p, &u);

	WREG32(CG_SSP, SSTU(u) | SST(p));
}