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
struct stv090x_state {TYPE_1__* internal; } ;
struct TYPE_2__ {int mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  SFRINIT0 ; 
 int /*<<< orphan*/  SFRINIT1 ; 
 scalar_t__ STV090x_WRITE_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int stv090x_set_srate(struct stv090x_state *state, u32 srate)
{
	u32 sym;

	if (srate > 60000000) {
		sym  = (srate << 4); /* SR * 2^16 / master_clk */
		sym /= (state->internal->mclk >> 12);
	} else if (srate > 6000000) {
		sym  = (srate << 6);
		sym /= (state->internal->mclk >> 10);
	} else {
		sym  = (srate << 9);
		sym /= (state->internal->mclk >> 7);
	}

	if (STV090x_WRITE_DEMOD(state, SFRINIT1, (sym >> 8) & 0x7f) < 0) /* MSB */
		goto err;
	if (STV090x_WRITE_DEMOD(state, SFRINIT0, (sym & 0xff)) < 0) /* LSB */
		goto err;

	return 0;
err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}