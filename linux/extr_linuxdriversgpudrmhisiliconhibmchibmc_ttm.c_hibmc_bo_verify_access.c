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
struct ttm_buffer_object {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vma_node; } ;
struct hibmc_bo {TYPE_1__ gem; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int drm_vma_node_verify_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hibmc_bo* hibmc_bo (struct ttm_buffer_object*) ; 

__attribute__((used)) static int hibmc_bo_verify_access(struct ttm_buffer_object *bo,
				  struct file *filp)
{
	struct hibmc_bo *hibmcbo = hibmc_bo(bo);

	return drm_vma_node_verify_access(&hibmcbo->gem.vma_node,
					  filp->private_data);
}