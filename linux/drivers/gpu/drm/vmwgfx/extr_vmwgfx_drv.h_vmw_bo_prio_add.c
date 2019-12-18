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
struct vmw_buffer_object {int /*<<< orphan*/ * res_prios; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmw_bo_prio_adjust (struct vmw_buffer_object*) ; 

__attribute__((used)) static inline void vmw_bo_prio_add(struct vmw_buffer_object *vbo, int prio)
{
	if (vbo->res_prios[prio]++ == 0)
		vmw_bo_prio_adjust(vbo);
}