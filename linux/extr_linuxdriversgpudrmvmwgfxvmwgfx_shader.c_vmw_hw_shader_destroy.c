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
struct vmw_resource {int id; TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct vmw_resource*) ;} ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/  (*) (struct vmw_resource*)) ; 
 int /*<<< orphan*/  stub1 (struct vmw_resource*) ; 

__attribute__((used)) static void vmw_hw_shader_destroy(struct vmw_resource *res)
{
	if (likely(res->func->destroy))
		(void) res->func->destroy(res);
	else
		res->id = -1;
}