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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDH_FLR_NOTIFICATION_CMPL ; 
 int xgpu_vi_poll_msg (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgpu_vi_wait_reset_cmpl(struct amdgpu_device *adev)
{
	return xgpu_vi_poll_msg(adev, IDH_FLR_NOTIFICATION_CMPL);
}