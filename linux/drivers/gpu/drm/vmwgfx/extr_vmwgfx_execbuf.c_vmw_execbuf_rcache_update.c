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
struct vmw_resource {int dummy; } ;
struct vmw_res_cache_entry {int valid; scalar_t__ valid_handle; void* private; struct vmw_resource* res; } ;

/* Variables and functions */

__attribute__((used)) static void vmw_execbuf_rcache_update(struct vmw_res_cache_entry *rcache,
				      struct vmw_resource *res,
				      void *private)
{
	rcache->res = res;
	rcache->private = private;
	rcache->valid = 1;
	rcache->valid_handle = 0;
}