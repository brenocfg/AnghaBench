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
struct mxs_lradc_ts {scalar_t__ base; struct mxs_lradc* lradc; } ;
struct mxs_lradc {size_t soc; } ;
struct TYPE_2__ {int /*<<< orphan*/  bit; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 scalar_t__ LRADC_CTRL0 ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 scalar_t__ STMP_OFFSET_REG_SET ; 
 TYPE_1__* info ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mxs_lradc_setup_touch_detection(struct mxs_lradc_ts *ts)
{
	struct mxs_lradc *lradc = ts->lradc;

	/*
	 * In order to detect a touch event the 'touch detect enable' bit
	 * enables:
	 *  - a weak pullup to the X+ connector
	 *  - a strong ground at the Y- connector
	 */
	writel(info[lradc->soc].mask,
	       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_CLR);
	writel(info[lradc->soc].bit,
	       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_SET);
}