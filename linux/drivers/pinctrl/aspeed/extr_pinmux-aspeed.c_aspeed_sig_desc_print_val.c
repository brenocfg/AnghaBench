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
struct aspeed_sig_desc {size_t ip; int mask; int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int __ffs (int) ; 
 int /*<<< orphan*/ * aspeed_pinmux_ips ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void aspeed_sig_desc_print_val(
		const struct aspeed_sig_desc *desc, bool enable, u32 rv)
{
	pr_debug("Want %s%X[0x%08X]=0x%X, got 0x%X from 0x%08X\n",
			aspeed_pinmux_ips[desc->ip], desc->reg,
			desc->mask, enable ? desc->enable : desc->disable,
			(rv & desc->mask) >> __ffs(desc->mask), rv);
}