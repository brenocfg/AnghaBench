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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_GCOOR ; 
 int PHC (int) ; 
 int SDC (int) ; 
 int SU (int) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r600_calculate_u_and_p (int,int,int,int*,int*) ; 
 int radeon_get_xclk (struct radeon_device*) ; 

__attribute__((used)) static void sumo_program_grsd(struct radeon_device *rdev)
{
	u32 p, u;
	u32 xclk = radeon_get_xclk(rdev);
	u32 grs = 256 * 25 / 100;

	r600_calculate_u_and_p(1, xclk, 14, &p, &u);

	WREG32(CG_GCOOR, PHC(grs) | SDC(p) | SU(u));
}