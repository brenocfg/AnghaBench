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
struct i915_request {struct i915_gem_context* gem_context; } ;
struct i915_gem_context {int remap_slice; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MAX_L3_SLICES ; 
 int remap_l3_slice (struct i915_request*,int) ; 

__attribute__((used)) static int remap_l3(struct i915_request *rq)
{
	struct i915_gem_context *ctx = rq->gem_context;
	int i, err;

	if (!ctx->remap_slice)
		return 0;

	for (i = 0; i < MAX_L3_SLICES; i++) {
		if (!(ctx->remap_slice & BIT(i)))
			continue;

		err = remap_l3_slice(rq, i);
		if (err)
			return err;
	}

	ctx->remap_slice = 0;
	return 0;
}