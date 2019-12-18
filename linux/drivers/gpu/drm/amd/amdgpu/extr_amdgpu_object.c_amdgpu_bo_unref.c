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
struct ttm_buffer_object {int dummy; } ;
struct amdgpu_bo {struct ttm_buffer_object tbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_bo_put (struct ttm_buffer_object*) ; 

void amdgpu_bo_unref(struct amdgpu_bo **bo)
{
	struct ttm_buffer_object *tbo;

	if ((*bo) == NULL)
		return;

	tbo = &((*bo)->tbo);
	ttm_bo_put(tbo);
	*bo = NULL;
}