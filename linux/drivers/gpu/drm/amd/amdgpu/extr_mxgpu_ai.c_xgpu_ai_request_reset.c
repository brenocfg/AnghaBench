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
 int /*<<< orphan*/  IDH_REQ_GPU_RESET_ACCESS ; 
 int xgpu_ai_send_access_requests (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgpu_ai_request_reset(struct amdgpu_device *adev)
{
	return xgpu_ai_send_access_requests(adev, IDH_REQ_GPU_RESET_ACCESS);
}