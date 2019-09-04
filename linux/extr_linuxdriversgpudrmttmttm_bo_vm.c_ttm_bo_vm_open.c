#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {TYPE_2__* vm_file; scalar_t__ vm_private_data; } ;
struct ttm_buffer_object {TYPE_1__* bdev; } ;
struct TYPE_4__ {scalar_t__ f_mapping; } ;
struct TYPE_3__ {scalar_t__ dev_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ttm_bo_get (struct ttm_buffer_object*) ; 

__attribute__((used)) static void ttm_bo_vm_open(struct vm_area_struct *vma)
{
	struct ttm_buffer_object *bo =
	    (struct ttm_buffer_object *)vma->vm_private_data;

	WARN_ON(bo->bdev->dev_mapping != vma->vm_file->f_mapping);

	ttm_bo_get(bo);
}