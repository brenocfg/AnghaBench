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
typedef  enum idh_request { ____Placeholder_idh_request } idh_request ;

/* Variables and functions */
 int IDH_REQ_GPU_FINI_ACCESS ; 
 int IDH_REQ_GPU_INIT_ACCESS ; 
 int xgpu_ai_send_access_requests (struct amdgpu_device*,int) ; 

__attribute__((used)) static int xgpu_ai_request_full_gpu_access(struct amdgpu_device *adev,
					   bool init)
{
	enum idh_request req;

	req = init ? IDH_REQ_GPU_INIT_ACCESS : IDH_REQ_GPU_FINI_ACCESS;
	return xgpu_ai_send_access_requests(adev, req);
}