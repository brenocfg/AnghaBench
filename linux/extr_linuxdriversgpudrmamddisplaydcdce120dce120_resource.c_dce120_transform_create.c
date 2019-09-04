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
typedef  size_t uint32_t ;
struct transform {int dummy; } ;
struct dce_transform {int lb_memory_size; struct transform base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dce_transform_construct (struct dce_transform*,struct dc_context*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dce_transform* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfm_mask ; 
 int /*<<< orphan*/ * xfm_regs ; 
 int /*<<< orphan*/  xfm_shift ; 

__attribute__((used)) static struct transform *dce120_transform_create(
	struct dc_context *ctx,
	uint32_t inst)
{
	struct dce_transform *transform =
		kzalloc(sizeof(struct dce_transform), GFP_KERNEL);

	if (!transform)
		return NULL;

	dce_transform_construct(transform, ctx, inst,
				&xfm_regs[inst], &xfm_shift, &xfm_mask);
	transform->lb_memory_size = 0x1404; /*5124*/
	return &transform->base;
}