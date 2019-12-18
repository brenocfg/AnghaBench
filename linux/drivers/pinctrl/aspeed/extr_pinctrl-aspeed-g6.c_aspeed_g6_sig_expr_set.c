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
typedef  int u32 ;
struct aspeed_sig_expr {int ndescs; struct aspeed_sig_desc* descs; } ;
struct aspeed_sig_desc {int enable; int disable; int mask; size_t ip; scalar_t__ reg; } ;
struct aspeed_pinmux_data {int /*<<< orphan*/ * maps; } ;

/* Variables and functions */
 size_t ASPEED_IP_SCU ; 
 int ENODEV ; 
 int EPERM ; 
 scalar_t__ SCU500 ; 
 scalar_t__ SCU510 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __ffs (int) ; 
 int aspeed_sig_expr_eval (struct aspeed_pinmux_data*,struct aspeed_sig_expr const*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int aspeed_g6_sig_expr_set(struct aspeed_pinmux_data *ctx,
				  const struct aspeed_sig_expr *expr,
				  bool enable)
{
	int ret;
	int i;

	for (i = 0; i < expr->ndescs; i++) {
		const struct aspeed_sig_desc *desc = &expr->descs[i];
		u32 pattern = enable ? desc->enable : desc->disable;
		u32 val = (pattern << __ffs(desc->mask));
		bool is_strap;

		if (!ctx->maps[desc->ip])
			return -ENODEV;

		WARN_ON(desc->ip != ASPEED_IP_SCU);
		is_strap = desc->reg == SCU500 || desc->reg == SCU510;

		if (is_strap) {
			/*
			 * The AST2600 has write protection mask registers for
			 * the hardware strapping in SCU508 and SCU518. Assume
			 * that if the platform doesn't want the strapping
			 * values changed that it has set the write mask.
			 *
			 * The strapping registers implement write-1-clear
			 * behaviour. SCU500 is paired with clear writes on
			 * SCU504, likewise SCU510 is paired with SCU514.
			 */
			u32 clear = ~val & desc->mask;
			u32 w1c = desc->reg + 4;

			if (clear)
				ret = regmap_update_bits(ctx->maps[desc->ip],
							 w1c, desc->mask,
							 clear);
		}

		ret = regmap_update_bits(ctx->maps[desc->ip], desc->reg,
					 desc->mask, val);
		if (ret)
			return ret;
	}

	ret = aspeed_sig_expr_eval(ctx, expr, enable);
	if (ret < 0)
		return ret;

	if (!ret)
		return -EPERM;
	return 0;
}