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
struct ttm_mem_reg {unsigned long num_pages; int /*<<< orphan*/  start; } ;
struct drm_mm_node {unsigned long start; unsigned long size; } ;

/* Variables and functions */
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void amdgpu_vram_mgr_virt_start(struct ttm_mem_reg *mem,
				       struct drm_mm_node *node)
{
	unsigned long start;

	start = node->start + node->size;
	if (start > mem->num_pages)
		start -= mem->num_pages;
	else
		start = 0;
	mem->start = max(mem->start, start);
}