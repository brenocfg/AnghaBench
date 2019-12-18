#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dc {TYPE_5__* current_state; } ;
struct TYPE_6__ {int /*<<< orphan*/  socclk_khz; int /*<<< orphan*/  fclk_khz; int /*<<< orphan*/  dppclk_khz; int /*<<< orphan*/  dispclk_khz; int /*<<< orphan*/  dcfclk_deep_sleep_khz; int /*<<< orphan*/  dcfclk_khz; } ;
struct TYPE_7__ {TYPE_1__ clk; } ;
struct TYPE_8__ {TYPE_2__ dcn; } ;
struct TYPE_9__ {TYPE_3__ bw; } ;
struct TYPE_10__ {TYPE_4__ bw_ctx; } ;

/* Variables and functions */
 unsigned int snprintf_count (char*,unsigned int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int dcn10_get_clock_states(struct dc *dc, char *pBuf, unsigned int bufSize)
{
	unsigned int chars_printed = 0;
	unsigned int remaining_buffer = bufSize;

	chars_printed = snprintf_count(pBuf, bufSize, "dcfclk,dcfclk_deep_sleep,dispclk,"
		"dppclk,fclk,socclk\n"
		"%d,%d,%d,%d,%d,%d\n",
		dc->current_state->bw_ctx.bw.dcn.clk.dcfclk_khz,
		dc->current_state->bw_ctx.bw.dcn.clk.dcfclk_deep_sleep_khz,
		dc->current_state->bw_ctx.bw.dcn.clk.dispclk_khz,
		dc->current_state->bw_ctx.bw.dcn.clk.dppclk_khz,
		dc->current_state->bw_ctx.bw.dcn.clk.fclk_khz,
		dc->current_state->bw_ctx.bw.dcn.clk.socclk_khz);

	remaining_buffer -= chars_printed;
	pBuf += chars_printed;

	return bufSize - remaining_buffer;
}