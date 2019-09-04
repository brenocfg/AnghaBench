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
struct pp_smu_funcs_rv {int dummy; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dm_pp_get_funcs_rv (struct dc_context*,struct pp_smu_funcs_rv*) ; 
 struct pp_smu_funcs_rv* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pp_smu_funcs_rv *dcn10_pp_smu_create(struct dc_context *ctx)
{
	struct pp_smu_funcs_rv *pp_smu = kzalloc(sizeof(*pp_smu), GFP_KERNEL);

	if (!pp_smu)
		return pp_smu;

	dm_pp_get_funcs_rv(ctx, pp_smu);
	return pp_smu;
}