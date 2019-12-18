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
struct TYPE_2__ {scalar_t__ ver; } ;
struct pp_smu_funcs {TYPE_1__ ctx; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PP_SMU_VER_NV ; 
 int /*<<< orphan*/  dm_pp_get_funcs (struct dc_context*,struct pp_smu_funcs*) ; 
 struct pp_smu_funcs* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct pp_smu_funcs* memset (struct pp_smu_funcs*,int /*<<< orphan*/ ,int) ; 

struct pp_smu_funcs *dcn20_pp_smu_create(struct dc_context *ctx)
{
	struct pp_smu_funcs *pp_smu = kzalloc(sizeof(*pp_smu), GFP_KERNEL);

	if (!pp_smu)
		return pp_smu;

	dm_pp_get_funcs(ctx, pp_smu);

	if (pp_smu->ctx.ver != PP_SMU_VER_NV)
		pp_smu = memset(pp_smu, 0, sizeof(struct pp_smu_funcs));

	return pp_smu;
}