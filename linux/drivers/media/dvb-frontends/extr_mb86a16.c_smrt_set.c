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
struct mb86a16_state {int deci; int master_clk; int csel; int rsel; } ;

/* Variables and functions */
 int /*<<< orphan*/  MB86A16_ERROR ; 
 int /*<<< orphan*/  MB86A16_SRATE1 ; 
 int /*<<< orphan*/  MB86A16_SRATE2 ; 
 int /*<<< orphan*/  MB86A16_SRATE3 ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ mb86a16_write (struct mb86a16_state*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int smrt_set(struct mb86a16_state *state, int rate)
{
	int tmp ;
	int m ;
	unsigned char STOFS0, STOFS1;

	m = 1 << state->deci;
	tmp = (8192 * state->master_clk - 2 * m * rate * 8192 + state->master_clk / 2) / state->master_clk;

	STOFS0 = tmp & 0x0ff;
	STOFS1 = (tmp & 0xf00) >> 8;

	if (mb86a16_write(state, MB86A16_SRATE1, (state->deci << 2) |
				       (state->csel << 1) |
					state->rsel) < 0)
		goto err;
	if (mb86a16_write(state, MB86A16_SRATE2, STOFS0) < 0)
		goto err;
	if (mb86a16_write(state, MB86A16_SRATE3, STOFS1) < 0)
		goto err;

	return 0;
err:
	dprintk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	return -1;
}