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
struct aspeed_sig_expr {int dummy; } ;
struct aspeed_pinmux_data {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set ) (struct aspeed_pinmux_data*,struct aspeed_sig_expr const*,int) ;} ;

/* Variables and functions */
 int stub1 (struct aspeed_pinmux_data*,struct aspeed_sig_expr const*,int) ; 

__attribute__((used)) static inline int aspeed_sig_expr_set(struct aspeed_pinmux_data *ctx,
				      const struct aspeed_sig_expr *expr,
				      bool enabled)
{
	return ctx->ops->set(ctx, expr, enabled);
}