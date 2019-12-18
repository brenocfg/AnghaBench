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
typedef  int /*<<< orphan*/  uint32_t ;
struct psb_mmu_pd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_ttm_cache_flush () ; 

__attribute__((used)) static void psb_mmu_flush_ptes(struct psb_mmu_pd *pd, unsigned long address,
			       uint32_t num_pages, uint32_t desired_tile_stride,
			       uint32_t hw_tile_stride)
{
	drm_ttm_cache_flush();
}