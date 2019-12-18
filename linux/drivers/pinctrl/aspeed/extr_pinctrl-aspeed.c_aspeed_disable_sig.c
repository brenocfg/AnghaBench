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
struct aspeed_sig_expr {int dummy; } ;
struct aspeed_pinmux_data {int dummy; } ;

/* Variables and functions */
 int aspeed_sig_expr_disable (struct aspeed_pinmux_data*,struct aspeed_sig_expr const*) ; 

__attribute__((used)) static int aspeed_disable_sig(struct aspeed_pinmux_data *ctx,
			      const struct aspeed_sig_expr **exprs)
{
	int ret = 0;

	if (!exprs)
		return true;

	while (*exprs && !ret) {
		ret = aspeed_sig_expr_disable(ctx, *exprs);
		exprs++;
	}

	return ret;
}