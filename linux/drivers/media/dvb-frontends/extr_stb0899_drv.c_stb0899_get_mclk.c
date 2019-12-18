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
typedef  int u32 ;
struct stb0899_state {int /*<<< orphan*/  verbose; TYPE_1__* config; } ;
struct TYPE_2__ {int xtal_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  STB0899_NCOARSE ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int) ; 
 int stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 stb0899_get_mclk(struct stb0899_state *state)
{
	u32 mclk = 0, div = 0;

	div = stb0899_read_reg(state, STB0899_NCOARSE);
	mclk = (div + 1) * state->config->xtal_freq / 6;
	dprintk(state->verbose, FE_DEBUG, 1, "div=%d, mclk=%d", div, mclk);

	return mclk;
}