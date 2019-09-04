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
 int /*<<< orphan*/  CG_LT ; 
 int /*<<< orphan*/  CG_RT ; 
 int FHS (int /*<<< orphan*/ ) ; 
 int FLS (int /*<<< orphan*/ ) ; 
 int FMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

void r600_set_at(struct radeon_device *rdev,
		 u32 l_to_m, u32 m_to_h,
		 u32 h_to_m, u32 m_to_l)
{
	WREG32(CG_RT, FLS(l_to_m) | FMS(m_to_h));
	WREG32(CG_LT, FHS(h_to_m) | FMS(m_to_l));
}