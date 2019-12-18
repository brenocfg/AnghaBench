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
struct vmw_sw_context {struct vmw_buffer_object* dx_query_mob; int /*<<< orphan*/  dx_query_ctx; int /*<<< orphan*/  ctx; } ;
struct vmw_buffer_object {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vmw_buffer_object* vmw_context_get_dx_query_mob (int /*<<< orphan*/ ) ; 
 int vmw_validation_res_reserve (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vmw_resources_reserve(struct vmw_sw_context *sw_context)
{
	int ret;

	ret = vmw_validation_res_reserve(sw_context->ctx, true);
	if (ret)
		return ret;

	if (sw_context->dx_query_mob) {
		struct vmw_buffer_object *expected_dx_query_mob;

		expected_dx_query_mob =
			vmw_context_get_dx_query_mob(sw_context->dx_query_ctx);
		if (expected_dx_query_mob &&
		    expected_dx_query_mob != sw_context->dx_query_mob) {
			ret = -EINVAL;
		}
	}

	return ret;
}