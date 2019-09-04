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
struct rdt_resource {int alloc_enabled; int /*<<< orphan*/  alloc_capable; } ;

/* Variables and functions */
 int EINVAL ; 
 struct rdt_resource* rdt_resources_all ; 
 int set_cache_qos_cfg (int,int) ; 

__attribute__((used)) static int cdp_enable(int level, int data_type, int code_type)
{
	struct rdt_resource *r_ldata = &rdt_resources_all[data_type];
	struct rdt_resource *r_lcode = &rdt_resources_all[code_type];
	struct rdt_resource *r_l = &rdt_resources_all[level];
	int ret;

	if (!r_l->alloc_capable || !r_ldata->alloc_capable ||
	    !r_lcode->alloc_capable)
		return -EINVAL;

	ret = set_cache_qos_cfg(level, true);
	if (!ret) {
		r_l->alloc_enabled = false;
		r_ldata->alloc_enabled = true;
		r_lcode->alloc_enabled = true;
	}
	return ret;
}