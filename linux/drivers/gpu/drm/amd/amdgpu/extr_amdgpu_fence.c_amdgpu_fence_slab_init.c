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
struct amdgpu_fence {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  amdgpu_fence_slab ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int amdgpu_fence_slab_init(void)
{
	amdgpu_fence_slab = kmem_cache_create(
		"amdgpu_fence", sizeof(struct amdgpu_fence), 0,
		SLAB_HWCACHE_ALIGN, NULL);
	if (!amdgpu_fence_slab)
		return -ENOMEM;
	return 0;
}