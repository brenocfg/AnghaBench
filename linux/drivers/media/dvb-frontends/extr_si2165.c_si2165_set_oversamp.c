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
typedef  int u64 ;
typedef  int u32 ;
struct si2165_state {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_OVERSAMP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int si2165_get_fe_clk (struct si2165_state*) ; 
 int si2165_writereg32 (struct si2165_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int si2165_set_oversamp(struct si2165_state *state, u32 dvb_rate)
{
	u64 oversamp;
	u32 reg_value;

	if (!dvb_rate)
		return -EINVAL;

	oversamp = si2165_get_fe_clk(state);
	oversamp <<= 23;
	do_div(oversamp, dvb_rate);
	reg_value = oversamp & 0x3fffffff;

	dev_dbg(&state->client->dev, "Write oversamp=%#x\n", reg_value);
	return si2165_writereg32(state, REG_OVERSAMP, reg_value);
}