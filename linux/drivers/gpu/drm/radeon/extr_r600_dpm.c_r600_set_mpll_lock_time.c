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
 int /*<<< orphan*/  MPLL_LOCK_TIME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPLL_LOCK_TIME_MASK ; 
 int /*<<< orphan*/  MPLL_TIME ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void r600_set_mpll_lock_time(struct radeon_device *rdev, u32 lock_time)
{
	WREG32_P(MPLL_TIME, MPLL_LOCK_TIME(lock_time), ~MPLL_LOCK_TIME_MASK);
}