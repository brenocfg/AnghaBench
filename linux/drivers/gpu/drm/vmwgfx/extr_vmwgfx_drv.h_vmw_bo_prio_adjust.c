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
struct TYPE_2__ {int priority; } ;
struct vmw_buffer_object {TYPE_1__ base; scalar_t__* res_prios; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 

__attribute__((used)) static inline void vmw_bo_prio_adjust(struct vmw_buffer_object *vbo)
{
	int i = ARRAY_SIZE(vbo->res_prios);

	while (i--) {
		if (vbo->res_prios[i]) {
			vbo->base.priority = i;
			return;
		}
	}

	vbo->base.priority = 3;
}