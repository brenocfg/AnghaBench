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
struct TYPE_2__ {int /*<<< orphan*/ * bo; } ;
struct vmw_buffer_object {TYPE_1__ map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_bo_kunmap (TYPE_1__*) ; 

void vmw_bo_unmap(struct vmw_buffer_object *vbo)
{
	if (vbo->map.bo == NULL)
		return;

	ttm_bo_kunmap(&vbo->map);
}