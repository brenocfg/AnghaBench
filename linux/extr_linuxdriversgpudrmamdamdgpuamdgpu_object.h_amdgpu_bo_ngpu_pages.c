#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_pages; } ;
struct amdgpu_bo {TYPE_1__ tbo; } ;

/* Variables and functions */
 int AMDGPU_GPU_PAGE_SIZE ; 
 int PAGE_SHIFT ; 

__attribute__((used)) static inline unsigned amdgpu_bo_ngpu_pages(struct amdgpu_bo *bo)
{
	return (bo->tbo.num_pages << PAGE_SHIFT) / AMDGPU_GPU_PAGE_SIZE;
}