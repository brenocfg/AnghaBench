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
typedef  int /*<<< orphan*/  u32 ;
struct petp {TYPE_1__* adapter; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ A_TP_GLOBAL_CONFIG ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void set_csum_offload(struct petp *tp, u32 csum_bit, int enable)
{
	u32 val = readl(tp->adapter->regs + A_TP_GLOBAL_CONFIG);

	if (enable)
		val |= csum_bit;
	else
		val &= ~csum_bit;
	writel(val, tp->adapter->regs + A_TP_GLOBAL_CONFIG);
}