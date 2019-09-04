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
 int cik_sdma_hw_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  cik_sdma_soft_reset (void*) ; 

__attribute__((used)) static int cik_sdma_resume(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	cik_sdma_soft_reset(handle);

	return cik_sdma_hw_init(adev);
}