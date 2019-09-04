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
 int /*<<< orphan*/  BRT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRT_MASK ; 
 int /*<<< orphan*/  VID_RT ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rv6xx_vid_response_set_brt(struct radeon_device *rdev, u32 rt)
{
	WREG32_P(VID_RT, BRT(rt), ~BRT_MASK);
}