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
typedef  int /*<<< orphan*/  u32 ;
struct dw_apb_timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APBTMR_CONTROL_INT ; 
 int /*<<< orphan*/  APBTMR_N_CONTROL ; 
 int /*<<< orphan*/  APBTMR_N_EOI ; 
 int /*<<< orphan*/  apbt_readl (struct dw_apb_timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apbt_writel (struct dw_apb_timer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apbt_enable_int(struct dw_apb_timer *timer)
{
	u32 ctrl = apbt_readl(timer, APBTMR_N_CONTROL);
	/* clear pending intr */
	apbt_readl(timer, APBTMR_N_EOI);
	ctrl &= ~APBTMR_CONTROL_INT;
	apbt_writel(timer, ctrl, APBTMR_N_CONTROL);
}