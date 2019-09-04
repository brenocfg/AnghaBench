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
struct dma_fence {int dummy; } ;
struct amdgpu_ib {int /*<<< orphan*/  sa_bo; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_sa_bo_free (struct amdgpu_device*,int /*<<< orphan*/ *,struct dma_fence*) ; 

void amdgpu_ib_free(struct amdgpu_device *adev, struct amdgpu_ib *ib,
		    struct dma_fence *f)
{
	amdgpu_sa_bo_free(adev, &ib->sa_bo, f);
}