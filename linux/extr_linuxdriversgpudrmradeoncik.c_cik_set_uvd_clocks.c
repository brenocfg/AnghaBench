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
 int /*<<< orphan*/  CG_DCLK_CNTL ; 
 int /*<<< orphan*/  CG_DCLK_STATUS ; 
 int /*<<< orphan*/  CG_VCLK_CNTL ; 
 int /*<<< orphan*/  CG_VCLK_STATUS ; 
 int cik_set_uvd_clock (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cik_set_uvd_clocks(struct radeon_device *rdev, u32 vclk, u32 dclk)
{
	int r = 0;

	r = cik_set_uvd_clock(rdev, vclk, CG_VCLK_CNTL, CG_VCLK_STATUS);
	if (r)
		return r;

	r = cik_set_uvd_clock(rdev, dclk, CG_DCLK_CNTL, CG_DCLK_STATUS);
	return r;
}