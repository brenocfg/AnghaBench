#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int symbol_rate; int clkdiv; int ratediv; } ;
struct cx24120_state {TYPE_2__ dnxt; TYPE_1__* i2c; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int cx24120_set_symbolrate(struct cx24120_state *state, u32 rate)
{
	dev_dbg(&state->i2c->dev, "(%d)\n", rate);

	state->dnxt.symbol_rate = rate;

	/* Check symbol rate */
	if (rate  > 31000000) {
		state->dnxt.clkdiv  = (-(rate < 31000001) & 3) + 2;
		state->dnxt.ratediv = (-(rate < 31000001) & 6) + 4;
	} else {
		state->dnxt.clkdiv  = 3;
		state->dnxt.ratediv = 6;
	}

	return 0;
}