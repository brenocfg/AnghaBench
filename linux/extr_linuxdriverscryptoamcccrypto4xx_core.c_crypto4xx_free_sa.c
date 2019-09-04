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
struct crypto4xx_ctx {scalar_t__ sa_len; int /*<<< orphan*/ * sa_out; int /*<<< orphan*/ * sa_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void crypto4xx_free_sa(struct crypto4xx_ctx *ctx)
{
	kfree(ctx->sa_in);
	ctx->sa_in = NULL;
	kfree(ctx->sa_out);
	ctx->sa_out = NULL;
	ctx->sa_len = 0;
}