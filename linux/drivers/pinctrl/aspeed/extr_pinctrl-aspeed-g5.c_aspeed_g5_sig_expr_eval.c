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
struct regmap {int dummy; } ;
struct aspeed_sig_expr {int ndescs; struct aspeed_sig_desc* descs; } ;
struct aspeed_sig_desc {size_t ip; } ;
struct aspeed_pinmux_data {int /*<<< orphan*/ * maps; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 struct regmap* aspeed_g5_acquire_regmap (struct aspeed_pinmux_data*,size_t) ; 
 int aspeed_sig_desc_eval (struct aspeed_sig_desc const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static int aspeed_g5_sig_expr_eval(struct aspeed_pinmux_data *ctx,
				   const struct aspeed_sig_expr *expr,
				   bool enabled)
{
	int ret;
	int i;

	for (i = 0; i < expr->ndescs; i++) {
		const struct aspeed_sig_desc *desc = &expr->descs[i];
		struct regmap *map;

		map = aspeed_g5_acquire_regmap(ctx, desc->ip);
		if (IS_ERR(map)) {
			dev_err(ctx->dev,
				"Failed to acquire regmap for IP block %d\n",
				desc->ip);
			return PTR_ERR(map);
		}

		ret = aspeed_sig_desc_eval(desc, enabled, ctx->maps[desc->ip]);
		if (ret <= 0)
			return ret;
	}

	return 1;
}