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
struct kvm_mmu_memory_cache {int nobjs; } ;

/* Variables and functions */

__attribute__((used)) static int mmu_memory_cache_free_objects(struct kvm_mmu_memory_cache *cache)
{
	return cache->nobjs;
}