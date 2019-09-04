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
struct mxs_lradc_ts {int /*<<< orphan*/  cur_plate; scalar_t__ base; struct mxs_lradc* lradc; } ;
struct mxs_lradc {size_t soc; } ;
struct TYPE_2__ {int /*<<< orphan*/  y_plate; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 scalar_t__ LRADC_CTRL0 ; 
 int /*<<< orphan*/  LRADC_SAMPLE_Y ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 scalar_t__ STMP_OFFSET_REG_SET ; 
 int /*<<< orphan*/  TOUCHSCREEN_VCHANNEL1 ; 
 int /*<<< orphan*/  TS_CH_XM ; 
 TYPE_1__* info ; 
 int /*<<< orphan*/  mxs_lradc_map_ts_channel (struct mxs_lradc_ts*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_lradc_setup_ts_channel (struct mxs_lradc_ts*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mxs_lradc_prepare_y_pos(struct mxs_lradc_ts *ts)
{
	struct mxs_lradc *lradc = ts->lradc;

	writel(info[lradc->soc].mask,
	       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_CLR);
	writel(info[lradc->soc].y_plate,
	       ts->base + LRADC_CTRL0 + STMP_OFFSET_REG_SET);

	ts->cur_plate = LRADC_SAMPLE_Y;
	mxs_lradc_map_ts_channel(ts, TOUCHSCREEN_VCHANNEL1, TS_CH_XM);
	mxs_lradc_setup_ts_channel(ts, TOUCHSCREEN_VCHANNEL1);
}