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
struct resource_pool {struct clock_source* dp_clock_source; } ;
struct resource_context {int /*<<< orphan*/  dp_clock_source_ref_count; int /*<<< orphan*/ * clock_source_ref_count; } ;
struct clock_source {int dummy; } ;

/* Variables and functions */
 int find_matching_clock_source (struct resource_pool const*,struct clock_source*) ; 

void resource_reference_clock_source(
		struct resource_context *res_ctx,
		const struct resource_pool *pool,
		struct clock_source *clock_source)
{
	int i = find_matching_clock_source(pool, clock_source);

	if (i > -1)
		res_ctx->clock_source_ref_count[i]++;

	if (pool->dp_clock_source == clock_source)
		res_ctx->dp_clock_source_ref_count++;
}