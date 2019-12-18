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
struct aspeed_sig_expr {int ndescs; struct aspeed_sig_desc* descs; } ;
struct aspeed_sig_desc {size_t ip; } ;
struct aspeed_pinmux_data {int /*<<< orphan*/ * maps; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* eval ) (struct aspeed_pinmux_data*,struct aspeed_sig_expr const*,int) ;} ;

/* Variables and functions */
 int aspeed_sig_desc_eval (struct aspeed_sig_desc const*,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct aspeed_pinmux_data*,struct aspeed_sig_expr const*,int) ; 

int aspeed_sig_expr_eval(struct aspeed_pinmux_data *ctx,
			 const struct aspeed_sig_expr *expr, bool enabled)
{
	int ret;
	int i;

	if (ctx->ops->eval)
		return ctx->ops->eval(ctx, expr, enabled);

	for (i = 0; i < expr->ndescs; i++) {
		const struct aspeed_sig_desc *desc = &expr->descs[i];

		ret = aspeed_sig_desc_eval(desc, enabled, ctx->maps[desc->ip]);
		if (ret <= 0)
			return ret;
	}

	return 1;
}