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
struct vmw_user_context {int /*<<< orphan*/  cotable_lock; struct vmw_resource** cotables; } ;
struct vmw_resource {int dummy; } ;

/* Variables and functions */
 int SVGA_COTABLE_DX10_MAX ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_resource_unreference (struct vmw_resource**) ; 

__attribute__((used)) static void vmw_context_cotables_unref(struct vmw_user_context *uctx)
{
	struct vmw_resource *res;
	int i;

	for (i = 0; i < SVGA_COTABLE_DX10_MAX; ++i) {
		spin_lock(&uctx->cotable_lock);
		res = uctx->cotables[i];
		uctx->cotables[i] = NULL;
		spin_unlock(&uctx->cotable_lock);

		if (res)
			vmw_resource_unreference(&res);
	}
}