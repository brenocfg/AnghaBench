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
struct TYPE_2__ {int cbm_len; int /*<<< orphan*/  shareable_bits; } ;
struct rdt_resource {int num_closid; int data_width; int alloc_capable; int alloc_enabled; TYPE_1__ cache; int /*<<< orphan*/  default_ctrl; } ;

/* Variables and functions */
 struct rdt_resource* rdt_resources_all ; 

__attribute__((used)) static void rdt_get_cdp_config(int level, int type)
{
	struct rdt_resource *r_l = &rdt_resources_all[level];
	struct rdt_resource *r = &rdt_resources_all[type];

	r->num_closid = r_l->num_closid / 2;
	r->cache.cbm_len = r_l->cache.cbm_len;
	r->default_ctrl = r_l->default_ctrl;
	r->cache.shareable_bits = r_l->cache.shareable_bits;
	r->data_width = (r->cache.cbm_len + 3) / 4;
	r->alloc_capable = true;
	/*
	 * By default, CDP is disabled. CDP can be enabled by mount parameter
	 * "cdp" during resctrl file system mount time.
	 */
	r->alloc_enabled = false;
}