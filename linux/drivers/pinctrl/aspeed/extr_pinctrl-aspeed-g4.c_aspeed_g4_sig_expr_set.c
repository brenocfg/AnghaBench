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
 int BIT (int) ; 
 int ENODEV ; 
 int EPERM ; 
 scalar_t__ HW_STRAP1 ; 
 scalar_t__ HW_STRAP2 ; 
 int __ffs (int) ; 
 int aspeed_sig_expr_eval (struct aspeed_pinmux_data*,struct aspeed_sig_expr const*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static int aspeed_g4_sig_expr_set(struct aspeed_pinmux_data *ctx,
				  const struct aspeed_sig_expr *expr,
				  bool enable)
{
	int ret;
	int i;

	for (i = 0; i < expr->ndescs; i++) {
		const struct aspeed_sig_desc *desc = &expr->descs[i];
		u32 pattern = enable ? desc->enable : desc->disable;
		u32 val = (pattern << __ffs(desc->mask));

		if (!ctx->maps[desc->ip])
			return -ENODEV;

		/*
		 * Strap registers are configured in hardware or by early-boot
		 * firmware. Treat them as read-only despite that we can write
		 * them. This may mean that certain functions cannot be
		 * deconfigured and is the reason we re-evaluate after writing
		 * all descriptor bits.
		 *
		 * Port D and port E GPIO loopback modes are the only exception
		 * as those are commonly used with front-panel buttons to allow
		 * normal operation of the host when the BMC is powered off or
		 * fails to boot. Once the BMC has booted, the loopback mode
		 * must be disabled for the BMC to control host power-on and
		 * reset.
		 */
		if (desc->ip == ASPEED_IP_SCU && desc->reg == HW_STRAP1 &&
		    !(desc->mask & (BIT(21) | BIT(22))))
			continue;

		if (desc->ip == ASPEED_IP_SCU && desc->reg == HW_STRAP2)
			continue;

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