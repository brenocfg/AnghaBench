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
 int gfx_v7_0_cp_resume (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_gpu_init (struct amdgpu_device*) ; 
 int gfx_v7_0_rlc_resume (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v7_0_hw_init(void *handle)
{
	int r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	gfx_v7_0_gpu_init(adev);

	/* init rlc */
	r = gfx_v7_0_rlc_resume(adev);
	if (r)
		return r;

	r = gfx_v7_0_cp_resume(adev);
	if (r)
		return r;

	return r;
}