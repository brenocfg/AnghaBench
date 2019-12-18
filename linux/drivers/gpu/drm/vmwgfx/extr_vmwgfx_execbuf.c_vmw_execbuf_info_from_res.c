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
struct vmw_sw_context {struct vmw_res_cache_entry* res_cache; } ;
struct vmw_resource {int dummy; } ;
struct vmw_res_cache_entry {struct vmw_ctx_validation_info* private; struct vmw_resource* res; scalar_t__ valid; } ;
struct vmw_ctx_validation_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 size_t vmw_res_type (struct vmw_resource*) ; 

__attribute__((used)) static struct vmw_ctx_validation_info *
vmw_execbuf_info_from_res(struct vmw_sw_context *sw_context,
			  struct vmw_resource *res)
{
	struct vmw_res_cache_entry *rcache =
		&sw_context->res_cache[vmw_res_type(res)];

	if (rcache->valid && rcache->res == res)
		return rcache->private;

	WARN_ON_ONCE(true);
	return NULL;
}