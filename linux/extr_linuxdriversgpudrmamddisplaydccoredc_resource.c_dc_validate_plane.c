#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dc_plane_state {int dummy; } ;
struct dc {int /*<<< orphan*/  caps; TYPE_2__* res_pool; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct TYPE_3__ {int (* validate_plane ) (struct dc_plane_state const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int DC_OK ; 
 int stub1 (struct dc_plane_state const*,int /*<<< orphan*/ *) ; 

enum dc_status dc_validate_plane(struct dc *dc, const struct dc_plane_state *plane_state)
{
	enum dc_status res = DC_OK;

	/* TODO For now validates pixel format only */
	if (dc->res_pool->funcs->validate_plane)
		return dc->res_pool->funcs->validate_plane(plane_state, &dc->caps);

	return res;
}