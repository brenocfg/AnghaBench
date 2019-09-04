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
struct dc_stream_state {int dummy; } ;
struct dc_state {int dummy; } ;
struct dc {int dummy; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;

/* Variables and functions */
 int DC_ERROR_UNEXPECTED ; 
 int DC_OK ; 
 int build_mapped_resource (struct dc*,struct dc_state*,struct dc_stream_state*) ; 
 int resource_map_clock_resources (struct dc*,struct dc_state*,struct dc_stream_state*) ; 
 int resource_map_pool_resources (struct dc*,struct dc_state*,struct dc_stream_state*) ; 

enum dc_status dce100_add_stream_to_ctx(
		struct dc *dc,
		struct dc_state *new_ctx,
		struct dc_stream_state *dc_stream)
{
	enum dc_status result = DC_ERROR_UNEXPECTED;

	result = resource_map_pool_resources(dc, new_ctx, dc_stream);

	if (result == DC_OK)
		result = resource_map_clock_resources(dc, new_ctx, dc_stream);

	if (result == DC_OK)
		result = build_mapped_resource(dc, new_ctx, dc_stream);

	return result;
}