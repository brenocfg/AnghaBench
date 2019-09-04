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
struct device {int dummy; } ;
struct caam_rng_ctx {scalar_t__ cur_buf_idx; scalar_t__ current_buf; struct device* jrdev; } ;

/* Variables and functions */
 int caam_init_buf (struct caam_rng_ctx*,int) ; 
 int rng_create_sh_desc (struct caam_rng_ctx*) ; 

__attribute__((used)) static int caam_init_rng(struct caam_rng_ctx *ctx, struct device *jrdev)
{
	int err;

	ctx->jrdev = jrdev;

	err = rng_create_sh_desc(ctx);
	if (err)
		return err;

	ctx->current_buf = 0;
	ctx->cur_buf_idx = 0;

	err = caam_init_buf(ctx, 0);
	if (err)
		return err;

	return caam_init_buf(ctx, 1);
}