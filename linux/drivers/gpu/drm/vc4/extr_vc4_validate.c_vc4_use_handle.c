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
typedef  size_t uint32_t ;
struct vc4_exec_info {int /*<<< orphan*/ * bo_index; } ;
struct drm_gem_cma_object {int dummy; } ;

/* Variables and functions */
 struct drm_gem_cma_object* vc4_use_bo (struct vc4_exec_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_gem_cma_object *
vc4_use_handle(struct vc4_exec_info *exec, uint32_t gem_handles_packet_index)
{
	return vc4_use_bo(exec, exec->bo_index[gem_handles_packet_index]);
}