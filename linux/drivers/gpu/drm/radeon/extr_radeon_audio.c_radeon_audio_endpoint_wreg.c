#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct radeon_device {TYPE_2__ audio; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* endpoint_wreg ) (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void radeon_audio_endpoint_wreg(struct radeon_device *rdev, u32 offset,
	u32 reg, u32 v)
{
	if (rdev->audio.funcs->endpoint_wreg)
		rdev->audio.funcs->endpoint_wreg(rdev, offset, reg, v);
}