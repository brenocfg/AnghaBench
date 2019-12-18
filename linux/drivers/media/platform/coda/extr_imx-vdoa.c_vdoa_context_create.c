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
struct vdoa_data {int /*<<< orphan*/  vdoa_clk; } ;
struct vdoa_ctx {struct vdoa_data* vdoa; int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vdoa_ctx*) ; 
 struct vdoa_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 

struct vdoa_ctx *vdoa_context_create(struct vdoa_data *vdoa)
{
	struct vdoa_ctx *ctx;
	int err;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return NULL;

	err = clk_prepare_enable(vdoa->vdoa_clk);
	if (err) {
		kfree(ctx);
		return NULL;
	}

	init_completion(&ctx->completion);
	ctx->vdoa = vdoa;

	return ctx;
}