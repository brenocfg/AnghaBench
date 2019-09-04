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
struct mxs_lradc_ts {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ LRADC_CTRL4 ; 
 int /*<<< orphan*/  LRADC_CTRL4_LRADCSELECT (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  LRADC_CTRL4_LRADCSELECT_MASK (unsigned int) ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 scalar_t__ STMP_OFFSET_REG_SET ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mxs_lradc_map_ts_channel(struct mxs_lradc_ts *ts, unsigned int vch,
				     unsigned int ch)
{
	writel(LRADC_CTRL4_LRADCSELECT_MASK(vch),
	       ts->base + LRADC_CTRL4 + STMP_OFFSET_REG_CLR);
	writel(LRADC_CTRL4_LRADCSELECT(vch, ch),
	       ts->base + LRADC_CTRL4 + STMP_OFFSET_REG_SET);
}