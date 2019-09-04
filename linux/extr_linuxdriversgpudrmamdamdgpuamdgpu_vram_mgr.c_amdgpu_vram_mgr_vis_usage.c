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
typedef  int /*<<< orphan*/  uint64_t ;
struct ttm_mem_type_manager {struct amdgpu_vram_mgr* priv; } ;
struct amdgpu_vram_mgr {int /*<<< orphan*/  vis_usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 

uint64_t amdgpu_vram_mgr_vis_usage(struct ttm_mem_type_manager *man)
{
	struct amdgpu_vram_mgr *mgr = man->priv;

	return atomic64_read(&mgr->vis_usage);
}