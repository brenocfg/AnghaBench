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
typedef  int /*<<< orphan*/  u8 ;
struct stb0899_state {int /*<<< orphan*/  verbose; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  STB0899_DISSTATUS ; 
 int /*<<< orphan*/  STB0899_GETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXIDLE ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int stb0899_wait_diseqc_txidle(struct stb0899_state *state, int timeout)
{
	u8 reg = 0;
	unsigned long start = jiffies;

	while (!STB0899_GETFIELD(TXIDLE, reg)) {
		reg = stb0899_read_reg(state, STB0899_DISSTATUS);
		if (time_after(jiffies, start + timeout)) {
			dprintk(state->verbose, FE_ERROR, 1, "timed out!!");
			return -ETIMEDOUT;
		}
		msleep(10);
	}
	return 0;
}