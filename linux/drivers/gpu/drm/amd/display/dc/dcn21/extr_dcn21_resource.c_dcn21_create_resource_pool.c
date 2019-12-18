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
struct resource_pool {int dummy; } ;
struct dcn21_resource_pool {struct resource_pool base; } ;
struct dc_init_data {int /*<<< orphan*/  num_virtual_links; } ;
struct dc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ construct (int /*<<< orphan*/ ,struct dc*,struct dcn21_resource_pool*) ; 
 int /*<<< orphan*/  kfree (struct dcn21_resource_pool*) ; 
 struct dcn21_resource_pool* kzalloc (int,int /*<<< orphan*/ ) ; 

struct resource_pool *dcn21_create_resource_pool(
		const struct dc_init_data *init_data,
		struct dc *dc)
{
	struct dcn21_resource_pool *pool =
		kzalloc(sizeof(struct dcn21_resource_pool), GFP_KERNEL);

	if (!pool)
		return NULL;

	if (construct(init_data->num_virtual_links, dc, pool))
		return &pool->base;

	BREAK_TO_DEBUGGER();
	kfree(pool);
	return NULL;
}