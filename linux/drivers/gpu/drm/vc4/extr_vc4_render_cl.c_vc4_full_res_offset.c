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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct vc4_exec_info {TYPE_1__* args; } ;
struct drm_vc4_submit_rcl_surface {scalar_t__ offset; } ;
struct drm_gem_cma_object {scalar_t__ paddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int VC4_TILE_BUFFER_SIZE ; 

__attribute__((used)) static uint32_t vc4_full_res_offset(struct vc4_exec_info *exec,
				    struct drm_gem_cma_object *bo,
				    struct drm_vc4_submit_rcl_surface *surf,
				    uint8_t x, uint8_t y)
{
	return bo->paddr + surf->offset + VC4_TILE_BUFFER_SIZE *
		(DIV_ROUND_UP(exec->args->width, 32) * y + x);
}