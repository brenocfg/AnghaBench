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
 int /*<<< orphan*/  cik_ctx_switch_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  cik_sdma_enable (struct amdgpu_device*,int) ; 
 int cik_sdma_gfx_resume (struct amdgpu_device*) ; 
 int cik_sdma_load_microcode (struct amdgpu_device*) ; 
 int cik_sdma_rlc_resume (struct amdgpu_device*) ; 

__attribute__((used)) static int cik_sdma_start(struct amdgpu_device *adev)
{
	int r;

	r = cik_sdma_load_microcode(adev);
	if (r)
		return r;

	/* halt the engine before programing */
	cik_sdma_enable(adev, false);
	/* enable sdma ring preemption */
	cik_ctx_switch_enable(adev, true);

	/* start the gfx rings and rlc compute queues */
	r = cik_sdma_gfx_resume(adev);
	if (r)
		return r;
	r = cik_sdma_rlc_resume(adev);
	if (r)
		return r;

	return 0;
}