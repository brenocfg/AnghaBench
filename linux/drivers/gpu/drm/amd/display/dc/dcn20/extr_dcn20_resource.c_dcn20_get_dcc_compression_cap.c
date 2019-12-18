#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dc_surface_dcc_cap {int dummy; } ;
struct dc_dcc_surface_param {int dummy; } ;
struct dc {TYPE_2__* res_pool; } ;
struct TYPE_6__ {TYPE_1__* funcs; } ;
struct TYPE_5__ {TYPE_3__* hubbub; } ;
struct TYPE_4__ {int (* get_dcc_compression_cap ) (TYPE_3__*,struct dc_dcc_surface_param const*,struct dc_surface_dcc_cap*) ;} ;

/* Variables and functions */
 int stub1 (TYPE_3__*,struct dc_dcc_surface_param const*,struct dc_surface_dcc_cap*) ; 

bool dcn20_get_dcc_compression_cap(const struct dc *dc,
		const struct dc_dcc_surface_param *input,
		struct dc_surface_dcc_cap *output)
{
	return dc->res_pool->hubbub->funcs->get_dcc_compression_cap(
			dc->res_pool->hubbub,
			input,
			output);
}