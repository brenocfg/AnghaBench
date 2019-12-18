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
typedef  int u8 ;
struct lgdt3305_state {TYPE_1__* cfg; } ;
typedef  enum lgdt3305_tp_valid_polarity { ____Placeholder_lgdt3305_tp_valid_polarity } lgdt3305_tp_valid_polarity ;
typedef  enum lgdt3305_tp_clock_mode { ____Placeholder_lgdt3305_tp_clock_mode } lgdt3305_tp_clock_mode ;
typedef  enum lgdt3305_tp_clock_edge { ____Placeholder_lgdt3305_tp_clock_edge } lgdt3305_tp_clock_edge ;
struct TYPE_2__ {int tpclk_edge; int tpclk_mode; int tpvalid_polarity; } ;

/* Variables and functions */
 int /*<<< orphan*/  LGDT3305_TP_CTRL_1 ; 
 int /*<<< orphan*/  lg_dbg (char*,int,int) ; 
 scalar_t__ lg_fail (int) ; 
 int lgdt3305_read_reg (struct lgdt3305_state*,int /*<<< orphan*/ ,int*) ; 
 int lgdt3305_soft_reset (struct lgdt3305_state*) ; 
 int lgdt3305_write_reg (struct lgdt3305_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lgdt3305_mpeg_mode_polarity(struct lgdt3305_state *state)
{
	u8 val;
	int ret;
	enum lgdt3305_tp_clock_edge edge = state->cfg->tpclk_edge;
	enum lgdt3305_tp_clock_mode mode = state->cfg->tpclk_mode;
	enum lgdt3305_tp_valid_polarity valid = state->cfg->tpvalid_polarity;

	lg_dbg("edge = %d, valid = %d\n", edge, valid);

	ret = lgdt3305_read_reg(state, LGDT3305_TP_CTRL_1, &val);
	if (lg_fail(ret))
		goto fail;

	val &= ~0x09;

	if (edge)
		val |= 0x08;
	if (mode)
		val |= 0x40;
	if (valid)
		val |= 0x01;

	ret = lgdt3305_write_reg(state, LGDT3305_TP_CTRL_1, val);
	if (lg_fail(ret))
		goto fail;

	ret = lgdt3305_soft_reset(state);
fail:
	return ret;
}