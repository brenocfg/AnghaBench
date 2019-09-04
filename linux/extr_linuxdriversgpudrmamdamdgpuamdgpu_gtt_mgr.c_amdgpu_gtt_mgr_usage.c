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
typedef  int uint64_t ;
struct ttm_mem_type_manager {int size; struct amdgpu_gtt_mgr* priv; } ;
struct amdgpu_gtt_mgr {int /*<<< orphan*/  available; } ;
typedef  int s64 ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int atomic64_read (int /*<<< orphan*/ *) ; 

uint64_t amdgpu_gtt_mgr_usage(struct ttm_mem_type_manager *man)
{
	struct amdgpu_gtt_mgr *mgr = man->priv;
	s64 result = man->size - atomic64_read(&mgr->available);

	return (result > 0 ? result : 0) * PAGE_SIZE;
}