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
struct vmw_ctx_binding_state {int /*<<< orphan*/  dirty; } ;
struct vmw_ctx_bindinfo {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMW_BINDING_RT_BIT ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vmw_ctx_binding_state* vmw_context_binding_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmw_binding_scrub_dx_rt(struct vmw_ctx_bindinfo *bi, bool rebind)
{
	struct vmw_ctx_binding_state *cbs =
		vmw_context_binding_state(bi->ctx);

	__set_bit(VMW_BINDING_RT_BIT, &cbs->dirty);

	return 0;
}