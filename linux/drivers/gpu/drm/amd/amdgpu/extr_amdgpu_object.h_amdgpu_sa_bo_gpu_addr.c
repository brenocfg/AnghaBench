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
typedef  scalar_t__ uint64_t ;
struct amdgpu_sa_bo {scalar_t__ soffset; TYPE_1__* manager; } ;
struct TYPE_2__ {scalar_t__ gpu_addr; } ;

/* Variables and functions */

__attribute__((used)) static inline uint64_t amdgpu_sa_bo_gpu_addr(struct amdgpu_sa_bo *sa_bo)
{
	return sa_bo->manager->gpu_addr + sa_bo->soffset;
}