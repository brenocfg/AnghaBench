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
 scalar_t__ CG_FFCT_0 ; 
 int DTC_0 (int) ; 
 int UTC_0 (int) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 

void r600_set_tc(struct radeon_device *rdev,
		 u32 index, u32 u_t, u32 d_t)
{
	WREG32(CG_FFCT_0 + (index * 4), UTC_0(u_t) | DTC_0(d_t));
}